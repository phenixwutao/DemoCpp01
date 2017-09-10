#include "stdafx.h"

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <list>
#include <memory>
#include <future>
#include <string>
#include <utility>
#include <chrono>
#include <algorithm>

#include "Chap04SynchronizingConcurrentOperations.h"
using namespace std;

bool flag = false;
std::mutex m;

void chap04TestWaitForEvent()
{
  unique_lock<mutex> lk(m);
  lk.unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  lk.lock();
}



struct data_chunk
{
  data_chunk() {}
  data_chunk(int id) : m_id(id){}
  int m_id = 6;
};

data_chunk prepare_data()
{
  static int id = 0;
  return data_chunk(id++);
}

void process(const data_chunk& data)
{
  cout << "processing " << data.m_id << endl;
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data_to_prepare()
{
  return data_queue.size() < 6;
}

bool is_last_chunk()
{
  return (data_queue.size() == 0);
}

void data_preparation_thread()
{
  while (more_data_to_prepare())
  {
    data_chunk const data = prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    cout << "data_preparation " << data.m_id << endl;
    data_cond.notify_one();
  }
}

void data_processing_thread()
{
  while (true)
  {
    // the waiting thread must unlock the mutex while it's waiting
    // and lock the mutex again afterward, so use unique_lock here:
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [] { return !data_queue.empty(); } );
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process(data);
    if (is_last_chunk())
      break;
  }
}

void chap04TestConditionVariables()
{
  std::thread t1(data_preparation_thread);
  std::thread t2(data_processing_thread);

  t1.join();
  t2.join();
}


template<typename T>
class threadsafe_queue
{
private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue()
  {}
  threadsafe_queue(threadsafe_queue const& other)
  {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue = other.data_queue;
  }

  size_t size()
  { 
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.size();
  }

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] {return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
    lk.unlock();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] {return !data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};


// example for a thread-safe queue
threadsafe_queue<data_chunk> safedata_queue;
data_chunk prepare_safedata()
{
  static int id = 0;
  return data_chunk(id++);
}

void safeprocess(const data_chunk& data)
{
  cout << "safeprocess " << data.m_id << endl;
}

bool more_safedata_to_prepare()
{
  return safedata_queue.size() < 6;
}

bool is_last_safechunk()
{
  return (safedata_queue.empty());
}

void safedata_preparation_thread()
{
  while (more_safedata_to_prepare())
  {
    data_chunk const data = prepare_safedata();
    safedata_queue.push(data);
    cout << "safedata_preparation " << data.m_id << endl;
  }
}

void safedata_processing_thread()
{
  while (true)
  {
    data_chunk data;
    safedata_queue.wait_and_pop(data);
    safeprocess(data);
    if (is_last_safechunk()) // break?
      break;
  }
}

void chap04TestThredasafeQueue()
{
  thread t1(safedata_preparation_thread);
  thread t2(safedata_processing_thread);
  t1.join();
  t2.join();
}

int find_the_answer_to_ltuae()
{
  return 42;
}

void chap04TestFutureGetReturnValueFromAsynchTask()
{
  std::future<int> wAnswer = std::async(find_the_answer_to_ltuae);
  // do other work
  cout << "async answer is " << wAnswer.get() << endl;
}


struct X
{
  void foo(int id, const std::string&  name)
  {
    cout << __func__ << " ---- " << id << " " << name << endl;
  }

  std::string bar(const std::string & name)
  {
    cout << __func__ << " ---- " << name << endl;
    return name;
  }
};



struct Y
{
  double operator()(double val)
  {
    cout << __func__ << " ---- " << val << endl;
    return val;
  }
};

X baz(X& rhs)
{
  cout << __func__ << " rhs copy" << endl;
  return rhs;
}

class move_only
{
public:
  move_only() {}
  move_only(move_only&&) {}
  move_only(move_only const&) = delete;
  move_only& operator=(move_only&&) {}
  move_only& operator=(move_only const&) = delete;
  void operator()() {}
};

void chap04TestAsynchTaskPassingArguments()
{
  cout << "---------------------------" << __func__ << endl;
  X x;
  auto f1 = std::async(&X::foo, &x, 42, string("hello")); // call function foo
  auto f2 = std::async(&X::bar, x, "goodbye"); // call function bar

  Y y;
  auto f3 = std::async(Y(), 3.141); // call move-constructed tmp Y()
  auto f4 = std::async(std::ref(y), 2.718); // call y(2.718)

  auto f5 = std::async(move_only()); // call std::move(move_only())

  auto f6 = std::async(baz, std::ref(x)); // call X baz(X& rhs)

}

void chap04TestAsyncOptions()
{
  cout << "---------------------------" << __func__ << endl;
  X x;
  auto f6 = std::async(std::launch::async, Y(), 1.2); // run in new thread

  auto f7 = std::async(std::launch::deferred, baz, std::ref(x)); // run in wait() or get()

  auto f8 = std::async(std::launch::deferred | std::launch::async,
                       baz, std::ref(x)); // implementation's choice

  auto f9 = std::async(baz, std::ref(x)); // implementation's choice
  f7.wait();
}


std::deque<std::packaged_task<void()> > tasks;
bool gui_shutdown_message_received() { return false; }
void get_and_process_gui_message() {}

void gui_thread()
{
  while (!gui_shutdown_message_received())
  {
    get_and_process_gui_message();
    std::packaged_task<void()> task;
    {
      std::lock_guard<std::mutex> lk(m);
      if (tasks.empty())
        continue;
      task = std::move(tasks.front());
      tasks.pop_front();
    }
    task();
  }
}

std::thread gui_bg_thread(gui_thread);

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
  std::packaged_task<void()> task(f);
  std::future<void> res = task.get_future();
  std::lock_guard<std::mutex> lk(m);
  tasks.push_back(std::move(task));
  return res;
}

// count down taking a second for each value:
int countdown(int from, int to) {
  for (int i = from; i != to; --i) {
    std::cout << i << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Lift off!\n" << endl;
  return from - to;
}

void chao04AssociatingTaskWithFuturePackagedTask()
{
  cout << "---------------------------" << __func__ << endl;
  std::packaged_task<int(int, int)> tsk(countdown);   // set up packaged_task
  std::future<int> ret = tsk.get_future();            // get future

  std::thread th(std::move(tsk), 3, 0);   // spawn thread to count down from 10 to 0

  int value = ret.get();                  // wait for the task to finish and get result

  std::cout << "The countdown lasted for " << value << " seconds.\n";

  th.join();
}

void print_int(std::future<int>& fut)
{
  int x = fut.get();
  std::cout << "value: " << x << '\n';
}

void chap04TestMakingPromise()
{
  std::promise<int> prom;                      // create promise

  std::future<int> fut = prom.get_future();    // engagement with future

  std::thread th1(print_int, std::ref(fut));  // send future to new thread

  prom.set_value(10);                         // fulfill promise
                                              // (synchronizes with getting the future)
  th1.join();
}

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
  if (input.empty())
  {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());

  T const& pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
    [&](T const& t) {return t < pivot; });

  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

  auto new_lower(  sequential_quick_sort(std::move(lower_part)) );
  auto new_higher( sequential_quick_sort(std::move(input)));
  result.splice(result.end(), new_higher);

  //Using synchronization of operations to simplify code
  result.splice(result.begin(), new_lower);
  return result;
}

void chap04TestSequentialQuickSort()
{
  list<int> mylist;
  mylist.push_back(10);
  mylist.push_back(5);
  mylist.push_back(7);
  mylist.push_back(3);
  mylist.push_back(6);
  mylist.push_front(20);
  mylist.push_front(15);
  mylist.push_front(17);
  mylist.push_front(8);
  mylist.push_front(13);
  auto srtList = sequential_quick_sort<int>(mylist);
  cout << __func__ << " ------- after sort:" << endl;
  for(const auto &item: srtList)
  {
    cout << item << endl;
  }
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
  if (input.empty())
  {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());

  T const& pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
    [&](T const& t) {return t < pivot; });

  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

  std::future<std::list<T> > new_lower(
    std::async(&parallel_quick_sort<T>, std::move(lower_part)));

  auto new_higher( parallel_quick_sort(std::move(input)) );
  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());

  return result;
}

void chap04TestParallelQuickSort()
{
  list<int> mylist;
  mylist.push_back(10);
  mylist.push_back(5);
  mylist.push_back(7);
  mylist.push_back(3);
  mylist.push_back(6);
  mylist.push_front(20);
  mylist.push_front(15);
  mylist.push_front(17);
  mylist.push_front(8);
  mylist.push_front(13);
  auto srtList = parallel_quick_sort<int>(mylist);
  cout << __func__ << " ------- after sort:" << endl;
  for (const auto &item : srtList)
  {
    cout << item << endl;
  }
}


