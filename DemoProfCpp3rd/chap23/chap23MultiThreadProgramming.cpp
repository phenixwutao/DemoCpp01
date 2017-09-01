#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <thread>
#include <exception>
#include <stdexcept>
#include <mutex>
#include <string>
#include <vector>
#include <atomic>

#include "chap23MultiThreadProgramming.h"

using namespace std;


void counter(int id, int numIterations)
{
  for (int i = 0; i < numIterations; ++i)
  {
    cout << "Counter " << id << " has value ";
    cout << i << endl;
  }
}

// P748
void chap23TestThreadWithFunctionPointer()
{
  thread t1(counter, 1, 6);
  thread t2(counter, 2, 4);
  t1.join();
  t2.join();
}

class Counter
{
public:
  Counter(int id, int numIterations)
    : mId(id), mNumIterations(numIterations)
  {
  }

  void operator()() const
  {
    for (int i = 0; i < mNumIterations; ++i) {
      cout << "Counter " << mId << " has value ";
      cout << i << endl;
    }
  }

private:
  int mId;
  int mNumIterations;
};


void chap23TestThreadWithFunctionObject()
{
  cout << __func__ << endl;
  thread t1(Counter(1, 6));
  thread t2{ Counter{2,5} };
  Counter cfunc(3, 4);
  thread t3(cfunc);

  t1.join();
  t2.join();
  t3.join();
}

void chap23TestThreadWithLambda()
{
  cout << __func__ << endl;

  int id = 1;
  int wMAX = 5;
  thread t1([id, wMAX] {
    for (int i = 0; i < wMAX; ++i)
      cout << "Counter " << id << " has value " << i << endl;
  }
  );

  t1.join();
}


class Request
{
public:
  Request(int id) : mId(id) { }

  void process()
  {
    cout << "Processing request " << mId << endl;
  }

private:
  int mId;
};

void chap23TestThreadWithMemberFunction()
{
  Request req(10);
  thread t1(&Request::process, &req);
}

void doSomeWork()
{
  for (int i = 0; i < 5; ++i) {
    cout << i << endl;
  }
  cout << "Thread throwing a runtime_error exception..." << endl;
  throw runtime_error("Exception from thread");
}

void threadFunc(exception_ptr& err)
{
  try {
    doSomeWork();
  }
  catch (...) {
    cout << "Thread caught exception, returning exception..." << endl;
    err = current_exception();
  }
}

void doWorkInThread()
{
  exception_ptr error;
  // Launch background thread
  thread t{ threadFunc, ref(error) };
  // Wait for thread to finish
  t.join();
  // See if thread has thrown any exception
  if (error) {
    cout << "Main thread received exception, rethrowing it..." << endl;
    rethrow_exception(error);
  }
  else {
    cout << "Main thread did not receive any exception." << endl;
  }
}

void chap23TestThreadWithExceptions()
{
  cout << __func__ << endl;

  try {
    doWorkInThread();
  }
  catch (const exception& e) {
    cout << "Main function caught: '" << e.what() << "'" << endl;
  }
}

/************************************************************************
* Every thread shares one-and-only-one copy of global variable, 
* While each thread has its own unique copy of thread_local variable.
*************************************************************************/
void chap23TestThreadLocalStorage()
{
  int wGlobal = 5;           // threads share only one copy
  thread_local int range = 5; // Each thread has a copy
  std::mutex cout_mutex;

  thread t1([&]() {
    std::lock_guard<std::mutex> lock(cout_mutex);
    range++;
    wGlobal = 1;
    cout << "t1 wGlobal "<< wGlobal  << ", range " << range << endl;
  });

  thread t2([&]() {
    std::lock_guard<std::mutex> lock(cout_mutex);
    range++;
    wGlobal = 2;
    cout << "t2 wGlobal " << wGlobal << ", range " << range << endl;
  });

  auto IncreaseRange = [&](const std::string& name) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    range +=2;
    wGlobal += 2;
    cout << name << " wGlobal=" << wGlobal << ", range=" << range << endl;
  };

  thread t3(IncreaseRange, "t3");

  {
    std::lock_guard<std::mutex> lock(cout_mutex);
    cout << "main wGlobal " << wGlobal << ", range " << range << endl;
  }
  
  t1.join();
  t2.join();
  t3.join();
}

void non_atomic_func(int& counter)
{
  for (int i = 0; i < 100; ++i) {
    ++counter;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void chap23TestNonAtomicOperation()
{
  std::cout << __func__ << std::endl;
  int counter = 0;
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; ++i) {
    threads.push_back(std::thread{ non_atomic_func, std::ref(counter) });
  }

  for (auto& t : threads) {
    t.join();
  }

  // the resulit is stochastic
  std::cout << "Result = " << counter << std::endl;
}

void atomic_func(std::atomic<int>& counter)
{
  for (int i = 0; i < 100; ++i) {
    ++counter;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

// using atomic type variable
void chap23TestAtomicOperation()
{
  std::cout << __func__ << std::endl;
  std::atomic<int> counter (0);
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; ++i) {
    threads.push_back(std::thread{ atomic_func, std::ref(counter) });
  }

  for (auto& t : threads) {
    t.join();
  }

  // the resulit is deterministic
  std::cout << "Result = " << counter << std::endl;
}

/************************************************************************
* Minimize the amount of synchronization, either atomics or explicit 
* synchronization, because it lowers performance.
*************************************************************************/
void atomic_func_optimise(std::atomic<int>& counter)
{
  int wResult = 0;
  for (int i = 0; i < 100; ++i) {
    ++wResult;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  counter += wResult;
}

void chap23TestAtomicOperationOptimised()
{
  std::cout << __func__ << std::endl;
  std::atomic<int> counter(0);
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; ++i) {
    threads.push_back(std::thread{ atomic_func_optimise, std::ref(counter) });
  }

  for (auto& t : threads) {
    t.join();
  }

  // the resulit is deterministic
  std::cout << "Result = " << counter << std::endl;
}

void chap23TestAtomicFetchAdd()
{
  std::cout << __func__ << std::endl;
  std::atomic<int> value(10);
  cout << "Value = " << value << endl;
  int fetched = value.fetch_add(4);
  cout << "Fetched = " << fetched << endl;
  cout << "Value = " << value << endl;
}
