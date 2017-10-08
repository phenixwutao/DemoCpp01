#include "StdAfx.h"

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>

#include <thread>
#include <mutex>
#include <chrono>

#include "ModernCpp.h"

using namespace std;

void func1()
{
  std::cout << "thread func without params" << std::endl;
}

void func2(int const i, double const d, std::string const s)
{
  std::cout << i << ", " << d << ", " << s << std::endl;
}

void func3(int & i)
{
  i *= 2;
}

inline void print_time()
{
  auto now = std::chrono::system_clock::now();
  auto stime = std::chrono::system_clock::to_time_t(now);
#pragma warning(disable : 4996)
  auto ltime = std::localtime(&stime);

  std::cout << std::put_time(ltime, "%c") << std::endl;

  // another way of get time
  time_t rawtime;
  time(&rawtime);
  tm tmp;
  auto errNum = localtime_s(&tmp, &rawtime);
  std::cout << std::put_time(&tmp, "%c") << std::endl;

}

void func4()
{
  using namespace std::chrono;

  print_time();

  std::this_thread::sleep_for(2s);

  print_time();
}

void func5()
{
  using namespace std::chrono;

  print_time();

  std::this_thread::sleep_until(
    std::chrono::system_clock::now() + 2s);

  print_time();
}

void func6(std::chrono::seconds timeout)
{
  auto now = std::chrono::system_clock::now();
  auto then = now + timeout;

  do
  {
    /*-------------------------------------------------------------------------------------
    * The calling thread yields, offering the implementation the opportunity to reschedule.
    * thread waits for other threads to advance without blocking.
    *-------------------------------------------------------------------------------------*/
    std::this_thread::yield();
  } while (std::chrono::system_clock::now() < then);
}


void Ch08_DemoWorkingWithThreads()
{
  FUNC_INFO;
  {
    PASS_INFO(1);
    std::thread t(func1);
    t.join();
  }

  {
    PASS_INFO(2);
    std::thread t([]() {
      std::cout << "thread func without params"
        << std::endl; });
    t.join();
  }

  {
    PASS_INFO(3);
    std::thread t(func2, 42, 42.0, "42");
    t.join();
  }

  {
    PASS_INFO(4);
    std::thread t(
      [](int const i, double const d, std::string const s)
        {
          std::cout << i << ", " << d << ", " << s << std::endl;
        },
      42, 42.0, "42");
    t.join();
  }

  {
    PASS_INFO(5);
    int n = 42;
    std::thread t(func3, std::ref(n));  // pass in reference
    t.join();

    std::cout << n << std::endl;
  }

  {
    PASS_INFO(6);
    int n = 42;   // pass in reference to lambda function
    std::thread t([](int & i) {i *= 2; }, std::ref(n));
    t.join();

    std::cout << n << std::endl;
  }

  {
    PASS_INFO(7);
    std::thread t(func4);
    t.join();
  }

  {
    PASS_INFO(8);
    std::thread t(func5);
    t.join();
  }

  {
    PASS_INFO(9);
    std::thread t(func6, std::chrono::seconds(2));
    t.join();

    print_time();
  }
}

/*------------------ demo exception handling in thread ----------------------*/
std::mutex                       g_mutex;
std::vector<std::exception_ptr>  g_exceptions;

void func1_exception()
{
  throw std::exception("exception 1");
}

void func2_exception()
{
  throw std::exception("exception 2");
}

void thread_func1_handle_exception()
{
  try
  {
    func1_exception();
  }
  catch (...)
  {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_exceptions.push_back(std::current_exception());
  }
}

void thread_func2_handle_exception()
{
  try
  {
    func2_exception();
  }
  catch (...)
  {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_exceptions.push_back(std::current_exception());
  }
}

void Ch08_DemoHandlingExceptionsFromThreadFunctions()
{
  FUNC_INFO;
  g_exceptions.clear();

  std::thread t1(thread_func1_handle_exception);
  std::thread t2(thread_func2_handle_exception);
  t1.join();
  t2.join();

  for (auto const & e : g_exceptions)
  {
    try
    {
      if (e != nullptr)
        std::rethrow_exception(e);
    }
    catch (std::exception const & ex)
    {
      std::cout << "Catch: " << ex.what() << std::endl;
    }
  }
}

/* ------ Demo Synchronizing Access To Shared Data With Mutexes And Locks ------*/
std::mutex g1_mutex;

void thread_process_func_1(int id)
{
  using namespace std::chrono_literals;

  std::lock_guard<std::mutex> lock(g1_mutex);
  std::cout << id << " running thread " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(2s);
  std::cout << id << " done in thread " << std::this_thread::get_id() << std::endl;
}

void thread_process_func_2(int id)
{
  using namespace std::chrono_literals;

  {
    std::lock_guard<std::mutex> lock(g1_mutex);
    std::cout << id << " running thread " << std::this_thread::get_id() << std::endl;
  }

  std::this_thread::yield();
  std::this_thread::sleep_for(2s);

  {
    std::lock_guard<std::mutex> lock(g1_mutex);
    std::cout << id << " done in thread " << std::this_thread::get_id() << std::endl;
  }
}

void thread_process_func_3()
{
  using namespace std::chrono_literals;

  g1_mutex.lock();
  std::cout << "running thread " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(2s);
  std::cout << "done in thread " << std::this_thread::get_id() << std::endl;
  g1_mutex.unlock();
}

template <class M>
class lock_guard
{
public:
  typedef M mutex_type;

  explicit lock_guard(M& Mtx) : mtx(Mtx)
  {
    mtx.lock();
  }

  lock_guard(M& Mtx, std::adopt_lock_t) : mtx(Mtx)
  {
  }

  ~lock_guard() noexcept
  {
    mtx.unlock();
  }

  lock_guard(const lock_guard&) = delete;
  lock_guard& operator=(const lock_guard&) = delete;
private:
  M& mtx;
};

template <typename T>
struct container
{
  std::mutex mutex;
  std::vector<T> data;
};

template <typename T>
void move_between(container<T> & c1, container<T> & c2,
  T const value)
{
  std::lock(c1.mutex, c2.mutex);

  std::lock_guard<std::mutex> l1(c1.mutex, std::adopt_lock);
  std::lock_guard<std::mutex> l2(c2.mutex, std::adopt_lock);

  c1.data.erase(
    std::remove(c1.data.begin(), c1.data.end(), value),
    c1.data.end());
  c2.data.push_back(value);
}

template <typename T>
void print_container(container<T> const & c)
{
  for (auto const & e : c.data)
    std::cout << e << ' ';
  std::cout << std::endl;
}

void Ch08_DemoSynchronizingAccessToSharedDataWithMutexesAndLocks()
{
  FUNC_INFO;
  {
    PASS_INFO(1);
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
      threads.emplace_back(thread_process_func_1, i+1);

    for (auto & t : threads)
      t.join();
  }

  {
    PASS_INFO(2);
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
      threads.emplace_back(thread_process_func_2, i+1);

    for (auto & t : threads)
      t.join();
  }

  {
    PASS_INFO(3);
    container<int> c1;
    c1.data.push_back(1);
    c1.data.push_back(2);
    c1.data.push_back(3);

    container<int> c2;
    c2.data.push_back(4);
    c2.data.push_back(5);
    c2.data.push_back(6);

    print_container(c1);
    print_container(c2);

    std::thread t1(move_between<int>, std::ref(c1), std::ref(c2), 3);
    std::thread t2(move_between<int>, std::ref(c2), std::ref(c1), 6);

    t1.join();
    t2.join();

    print_container(c1);
    print_container(c2);

  }
}
