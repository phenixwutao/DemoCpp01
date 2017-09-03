#include "stdafx.h"

#include <iostream>
#include <string>
#include <thread>
#include <exception>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

#include "chap02DemoThreadManagement.h"

using namespace std;

class background_task
{
public:
  void do_something()
  {
    cout << "do_something" << endl;
  }

  void do_something_else()
  {
    cout << "do_something_else" << endl;
  }

  void operator()()
  {
    do_something();
    do_something_else();
  }
};

void chap02ThreadStart()
{
  //// standard way of thread object
  background_task f;
  std::thread my_thread(f);
  my_thread.join();
  cout << "----------------------- 1" << endl;

  //// thread object by C++ initialization
  thread t { background_task() };
  t.join();
  cout << "----------------------- 2" << endl;


  // thread object by lambda
  thread t2( [] () {
    background_task f;
    f.do_something();
    f.do_something_else();
  });
  t2.join();
  cout << "----------------------- 3" << endl;
}

void do_something_calc(int& i)
{
  ++i;
}

struct FuncCalc
{
  int& i;

  FuncCalc(int& i_) :i(i_) {}

  void operator()()
  {
    for (unsigned j = 0; j<1000000; ++j)
    {
      do_something_calc(i);
    }
  }
};

/*
* Call this function will crash
*/
void chap02ThreadInvalidReference()
{
  int some_local_state = 0;
  FuncCalc my_func_calc(some_local_state);
  std::thread my_thread(my_func_calc);
  my_thread.detach();
}

void do_something_in_current_thread()
{
  //throw::runtime_error("error in_current_thread!");
}

void chap02ThreadInvalidReferenceFix()
{
  int some_local_state = 0;
  FuncCalc my_func_calc(some_local_state);
  std::thread t(my_func_calc);
  try
  {
    // any exception could be thrown in the function
    do_something_in_current_thread();
  }
  catch (...)
  {
    cout << "catch exception here ... ..." << endl;
    t.join();
    throw;
  }

  // garantee reference to local varibale is valid
  t.join();
  cout << "work as normal here ... ..." << endl;
}

void chap02TestThreadGuard()
{
  int some_local_state = 0;
  FuncCalc my_func_calc(some_local_state);
  std::thread t(my_func_calc);
  thread_guard g(t);
  do_something_in_current_thread();
}

void do_background_work() {}

void chap02TestDaemonThreads()
{
  std::thread t(do_background_work);
  t.detach();
  auto fCanJoin = t.joinable();
  cout << (fCanJoin ? "Can join" : "Cannot join") << endl;
}

void PassParameter(int i, std::string const& s) {
  cout << __func__ << " " << i << " " << s << endl;
}

void chap02TestThreadPassParameter()
{
  char buffer[1024]; // 1
  sprintf_s(buffer, "%s", "test hello");
  std::thread t(PassParameter, 3, std::string(buffer)); // 2
  t.detach();
}


void update_data_for_widget(unsigned int w, string& data) // 1
{
  cout << __func__ << " " << w << " " << data << endl;
}

void chap02TestThreadPassReference(unsigned int w)
{
  string data;
  // use std::ref to pass a reference, not a copy
  std::thread t(update_data_for_widget, w, std::ref(data)); // 2

  t.join();

  // process un-updated data if not pass in by std::ref
  //process_widget_data(data); // 3
}

class FuncParam
{
public:
  void do_lengthy_work1() {}

  void do_lengthy_work2(int num) {
    cout << "do_lengthy_work2 " << num << endl;
  }
};

void chap02TestThreadBindFunc()
{
  FuncParam my_x;
  // thread function is FuncParam::do_lengthy_work1
  // address is: &my_x
  std::thread t(&FuncParam::do_lengthy_work1, &my_x); // 1
  t.join();
}

void chap02TestThreadBindFuncParameters()
{
  FuncParam my_x;
  // thread function is FuncParam::do_lengthy_work2
  // address is: &my_x
  // thread function parameter: int num
  int num = 9;
  std::thread t(&FuncParam::do_lengthy_work2, &my_x, num); // 1
  t.join();
}

void process_big_object(std::unique_ptr<string> p)
{
  cout << __func__ << " : " << p.get()->c_str() << endl;
}

void chap02TestThreadMoveParameter()
{
  std::unique_ptr<string> p(new string("Big data"));
  std::thread t(process_big_object, std::move(p));
  t.join();
}

class scoped_thread
{
private:
  std::thread t;

public:
  explicit scoped_thread(std::thread t_) :
    t(std::move(t_))
  {
    if (!t.joinable())
      throw std::logic_error("No thread");
  }
  ~scoped_thread()
  {
    t.join();
  }
  scoped_thread(scoped_thread const&) = delete;
  scoped_thread& operator=(scoped_thread const&) = delete;
};


void MoveCalcOperation(int& i)
{
  ++i;
}

struct FuncMove
{
  int& i;

  FuncMove(int& i_) :i(i_) {}

  void operator()()
  {
    for (unsigned j = 0; j<1000000; ++j)
    {
      MoveCalcOperation(i);
    }
    cout << __func__ << ": value=" << i << endl;
  }
};

void chap02TestThreadScopedThread()
{
  int some_local_state = 0;
  // move thread object
  scoped_thread t(std::thread { FuncMove(some_local_state) } );

  do_something_in_current_thread();
}

void thread_function()
{
  cout << "---------------------------" << __func__ << endl;
}

void other_thread_function()
{
  cout << "---------------------------" << __func__ << endl;
}

void chap02TestThreadTransferFunctionOwnership()
{
  std::thread t1(thread_function); // 1: thread t1 -> thread_function
  std::thread t2 = std::move(t1);  // 2: thread t1 moved into t2, t2 -> thread_function
  t1 = std::thread(other_thread_function); // 3 implcitly call std::move for temp object
  std::thread t3; // 4: thread t3 without any function
  t3 = std::move(t2); // 5: move thread t2 into t3, t3 -> thread_function

  try {
    t1 = std::move(t3); // 6: trigger terminate to crash by this assignment operation
  }
  catch (...)
  {
    cout << "catch exception when moving..." << endl;
  }
}

/*-------------------------- move thread itself ------------------------------*/
void NormalFunc()
{
  cout << "---------------------------" << __func__ << endl;
}

// thread ownership can be transferred
std::thread FetchThread()
{
  return std::thread(NormalFunc);
}

void NormalFuncParameter(int num)
{
  cout << "---------------------------" << __func__ << " "<<num <<endl;
}

// thread ownership can be transferred
std::thread FetchThreadParameter()
{
  std::thread t(NormalFuncParameter, 42);
  return t;
}

void chap02TestThreadTransferThreadOwnership()
{
  auto t1 = FetchThread();
  t1.join();

  auto t2 = FetchThreadParameter();
  t2.join();
}

void PassThreadParameter(std::thread t)
{
  if (t.joinable() == true)
    t.join();
}

void chap02TestThreadTransferThreadOwnershipInFunction()
{
  cout << "---------------------------" << __func__ << endl;
  PassThreadParameter(std::thread(NormalFunc));
  thread t(NormalFunc);
  PassThreadParameter(std::move(t));
}


void do_work(int num)
{
  cout << "---------------------------" << __func__ << ": " << num << endl;
}

void chap02TestThreadInVector()
{
  cout << "---------------------------" << __func__ << endl;
  std::vector<std::thread> threads;
  for (unsigned i = 0; i<20; ++i)
  {
    threads.push_back(std::thread(do_work, i));
  }
  // Call join for each thread
  std::for_each(threads.begin(), threads.end(),
    std::mem_fn(&std::thread::join));
}

/********************** Thread Concurrent Accumulate****************************/
template<typename Iterator, typename T>
struct accumulate_block
{
  void operator()(Iterator first, Iterator last, T& result)
  {
    result = std::accumulate(first, last, result);
  }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
  unsigned long const length = std::distance(first, last);

  if (!length)
    return init;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
    (length + min_per_thread - 1) / min_per_thread;

  unsigned long const hardware_threads = std::thread::hardware_concurrency();
  cout << "hardware_threads: " << hardware_threads << endl;

  unsigned long const num_threads =
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length / num_threads;

  std::vector<T> results(num_threads);
  std::vector<std::thread>  threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i<(num_threads - 1); ++i)
  {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(
      accumulate_block<Iterator, T>(),
      block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }
  accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

  std::for_each(threads.begin(), threads.end(),
    std::mem_fn(&std::thread::join));

  return std::accumulate(results.begin(), results.end(), init);
}

void chap02TestThreadConcurrentAccumulate()
{
  cout << "---------------------------" << __func__ << endl;
  std::vector<int> vi;
  for (int i = 0; i<10; ++i) {
    vi.push_back(10);
  }

  int sum = parallel_accumulate(vi.begin(), vi.end(), 5);
  std::cout << "sum=" << sum << std::endl;
}
