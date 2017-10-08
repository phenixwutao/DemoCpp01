#include "StdAfx.h"

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <array>
#include <queue>

#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <future>

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

  /*-------------------------------------------------------------------------------------------------
  * std::defer_lock, std::try_to_lock and std::adopt_lock are instances of empty struct tag types 
  * std::defer_lock_t, std::try_to_lock_t and std::adopt_lock_t respectively.
  *
  * They are used to specify locking strategies for std::lock_guard, std::unique_lock and std::shared_lock.

  * --- Type ---    --- Effect(s) ---
  * defer_lock_t	  do not acquire ownership of the mutex
  * try_to_lock_t	  try to acquire ownership of the mutex without blocking
  * adopt_lock_t	  assume the calling thread already has ownership of the mutex
  *------------------------------------------------------------------------------------------------*/
  std::lock_guard<std::mutex> l1(c1.mutex, std::adopt_lock);
  std::lock_guard<std::mutex> l2(c2.mutex, std::adopt_lock);

  // equivalent approach:
  //std::unique_lock<std::mutex> lock1(c1.mutex, std::defer_lock);
  //std::unique_lock<std::mutex> lock2(c2.mutex, std::defer_lock);
  //std::lock(lock1, lock2);

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

class foo_recursive
{
  std::recursive_mutex m;
  int data;

public:
  foo_recursive(int const d = 0) : data(d) {}

  void update(int const d)
  {
    std::lock_guard<std::recursive_mutex> lock(m);
    data = d;
    cout << std::this_thread::get_id() << " data =" << data << endl;
  }

  int update_with_return(int const d)
  {
    std::lock_guard<std::recursive_mutex> lock(m);
    auto temp = data;
    update(d);
    return temp;
  }

  void PrintInfo()
  {
    cout << std::this_thread::get_id() << " data =" << data << endl;
  }
};

class foo_normal
{
  std::mutex m;
  int data;

public:
  void internal_update(int const d) { data = d; }

  foo_normal(int const d = 0) : data(d) {}

  void update(int const d)
  {
    std::lock_guard<std::mutex> lock(m);
    internal_update(d);
    cout << std::this_thread::get_id() << " data =" << data << endl;
  }

  int update_with_return(int const d)
  {
    std::lock_guard<std::mutex> lock(m);
    auto temp = data;
    internal_update(d);
    return temp;
  }

  void PrintInfo()
  {
    cout << std::this_thread::get_id() << " data =" << data << endl;
  }
};

void Ch08_DemoAvoidingUsingRecursiveMutexes()
{
  FUNC_INFO;
  PASS_INFO(1);
  foo_normal foo(1);
  foo.PrintInfo();
  std::thread thrd(&foo_normal::update, &foo, std::move(2));
  thrd.join();
  foo.PrintInfo();

  PASS_INFO(2);
  foo_recursive foo_rec(3);
  foo_rec.PrintInfo();
  std::thread thrd_rec(&foo_recursive::update, &foo_rec, std::move(4));
  thrd_rec.join();
  foo_rec.PrintInfo();
}

/*---------------- DemoSendingNotificationsBetweenThreads ----------------*/
using namespace std::chrono_literals;

std::mutex              g_lockprint;
std::mutex              g_lockqueue;
std::condition_variable g_queuecheck;
std::queue<int>         g_buffer;
bool                    g_done;

void producer(int const id,
              std::mt19937& generator,
              std::uniform_int_distribution<int>& dsleep,
              std::uniform_int_distribution<int>& dcode)
{
  for (int i = 0; i < 5; ++i)
  {
    // simulate work
    std::this_thread::sleep_for(std::chrono::seconds(dsleep(generator)));

    // generate data
    int value = id * 100 + dcode(generator);

    {
      std::unique_lock<std::mutex> locker(g_lockprint);
      std::cout << "[produced]: " << value << std::endl;
    }

    // notify consumers
    {
      std::unique_lock<std::mutex> locker(g_lockqueue);
      g_buffer.push(value);
      g_queuecheck.notify_one();
    }
  }
}

void consumer()
{
  // loop until end is signaled
  while (!g_done)
  {
    std::unique_lock<std::mutex> locker(g_lockqueue);

    g_queuecheck.wait(locker, [&]() {return !g_buffer.empty(); });

    // if there are values in the queue process them
    while (!g_buffer.empty())
    {
      std::unique_lock<std::mutex> locker(g_lockprint);
      std::cout << "[consumed]: " << g_buffer.front() << std::endl;
      g_buffer.pop();
    }
  }
}

void Ch08_DemoSendingNotificationsBetweenThreads()
{
  FUNC_INFO;
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::random_device rd {};

  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  auto generator = std::mt19937{ seq };
  auto dsleep = std::uniform_int_distribution<>{ 1, 5 };
  auto dcode = std::uniform_int_distribution<>{ 1, 99 };

  std::cout << "start producing and consuming..." << std::endl;

  std::thread consumerthread(consumer);

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i)
  {
    threads.emplace_back(producer,
                         i + 1,
                         std::ref(generator),
                         std::ref(dsleep),
                         std::ref(dcode));
  }

  PASS_INFO(1);
  // work for the workers to finish
  for (auto& t : threads)
    t.join();

  PASS_INFO(2);
  // notify the logger to finish and wait for it
  g_done = true;
  consumerthread.join();

  std::cout << "done producing and consuming" << std::endl;
}

/*------------------------ demo promise and future ------------------------*/
std::mutex g2_mutex;

void produce_value(std::promise<int>& p)
{
  // simulate long running operation
  {
    using namespace std::chrono_literals;
    printf("sleep_for(2000ms)\n");
    std::this_thread::sleep_for(2000ms);
  }

  p.set_value(42);
}

void consume_value(std::future<int>& f)
{
  auto value = f.get();

  std::lock_guard<std::mutex> lock(g2_mutex);
  std::cout << "future get value "<< value << std::endl;
}

void Ch08_DemoUsingPromisesAndFuturesFromThreads()
{
  FUNC_INFO;
  std::promise<int> p;
  std::thread t1(produce_value, std::ref(p));

  std::future<int> f = p.get_future();
  std::thread t2(consume_value, std::ref(f));

  t1.join();
  t2.join();
}


std::mutex g3_mutex;

void do_something()
{
  // simulate long running operation
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
  }

  std::lock_guard<std::mutex> lock(g3_mutex);
  std::cout << "operation 1 done" << std::endl;
}

void do_something_else()
{
  // simulate long running operation
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
  }

  std::lock_guard<std::mutex> lock(g3_mutex);
  std::cout << "operation 2 done" << std::endl;
}

int compute_something()
{
  // simulate long running operation
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
  }

  return 42;
}

int compute_something_else()
{
  // simulate long running operation
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
  }

  return 24;
}

void Ch08_DemoExecutingFunctionsAsynchronously()
{
  FUNC_INFO;
  {
    PASS_INFO(1);
    // Use the std::launch::async policy of the first argument to the function to
    // make sure the function does run asynchronously
    auto f = std::async(std::launch::async, do_something);

    // check future status by wait_for
    while (true)
    {
      using namespace std::chrono_literals;
      auto status = f.wait_for(500ms);

      if (status == std::future_status::ready)
        break;

      std::cout << "waiting..." << std::endl;
    }

    std::cout << "done!" << std::endl;
    do_something_else();

    f.wait(); // Make sure the asynchronous operation is completed

    std::cout << "all done!" << std::endl;
  }

  {
    PASS_INFO(2);
    auto f = std::async(std::launch::async, compute_something);

    auto value = compute_something_else();

    value += f.get();

    std::cout << value << std::endl;
  }
}

#include <atomic>
#include <cassert>
#include <numeric>

void test_atomic()
{
  SUBFUNC_INFO;
  std::atomic<int> counter{ 0 };

  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i)
  {
    threads.emplace_back([&counter]() {
      for (int i = 0; i < 10; ++i)
        ++counter;
    });
  }

  for (auto & t : threads) t.join();

  std::cout << counter << std::endl;
}

void test_atomic_flag()
{
  SUBFUNC_INFO;
  std::atomic_flag lock = ATOMIC_FLAG_INIT;
  int counter = 0;

  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i)
  {
    threads.emplace_back([&]() {
      while (lock.test_and_set(std::memory_order_acquire));
      ++counter;
      lock.clear(std::memory_order_release);
    });
  }

  for (auto & t : threads) t.join();

  std::cout << counter << std::endl;
}

std::vector<int> generate_random()
{
  std::random_device rd;
  auto generator = std::mt19937{ rd() };
  auto dis = std::uniform_int_distribution<>{ 1, 99 };
  std::vector<int> numbers(100000, 0);
  std::generate(std::begin(numbers), std::end(numbers), [&dis, &generator] {return dis(generator); });

  return numbers;
}

void test_fetch_arithmetic()
{
  SUBFUNC_INFO;
  std::atomic<int> sum{ 0 };
  std::vector<int> numbers = generate_random();

  auto sum_expected = std::accumulate(std::begin(numbers), std::end(numbers), 0);

  size_t size = numbers.size();
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i)
  {
    threads.emplace_back([&sum, &numbers](size_t const start, size_t const end)
      {
        for (size_t i = start; i < end; ++i)
        {
          std::atomic_fetch_add_explicit(&sum, numbers[i], std::memory_order_acquire);
        }
      },
      i*(size / 10),
      (i + 1)*(size / 10));
  }

  for (auto & t : threads) t.join();

  assert(sum == sum_expected);
  std::cout << sum << std::endl;
  std::cout << sum_expected << std::endl;
}


template <typename T,
  typename I = typename std::enable_if<std::is_integral<T>::value>::type>
  class atomic_counter
{
  std::atomic<T> counter{ 0 };
public:
  T increment()
  {
    return counter.fetch_add(1);
  }

  T decrement()
  {
    return counter.fetch_sub(1);
  }

  T get()
  {
    return counter.load();
  }
};

void test_counter()
{
  SUBFUNC_INFO;
  atomic_counter<int> counter;

  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i)
  {
    threads.emplace_back([&counter]() {
      for (int i = 0; i < 10; ++i)
        counter.increment();
    });
  }

  for (auto & t : threads) t.join();

  std::cout << counter.get() << std::endl;
}

void Ch08_DemoUsingAtomicTypes()
{
  FUNC_INFO;
  test_atomic();
  test_atomic_flag();
  test_fetch_arithmetic();
  test_counter();
}
