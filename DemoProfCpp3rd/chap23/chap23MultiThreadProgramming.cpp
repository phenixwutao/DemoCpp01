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
#include <chrono>
#include <future>
#include <sstream>

#include "chap23MultiThreadProgramming.h"
#include "Logger.h"

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

/****************************************************************************
* The instance of std::defer_lock_t as a second argument to tell unique_lock
* not to acquire the lock during construction. The call to lock() then 
* acquires both locks without the risk of deadlocks
*****************************************************************************/
void chap23TestMultipleLocks()
{
  std::mutex mut1;
  std::mutex mut2;
  std::unique_lock<mutex> lock1(mut1, defer_lock_t());
  std::unique_lock<mutex> lock2(mut2, defer_lock_t());
  std::lock(lock1, lock2);
}


once_flag gOnceFlag;

void initializeSharedResources()
{
  // ... Initialize shared resources that will be used by multiple threads.

  cout << "Shared resources initialized." << endl;
}

/******************************************************************
* Shared resources should be initialized only once by calling 
* initializeSharedResources()  once.
*******************************************************************/
void processingFunction()
{
  // Make sure the shared resources are initialized.
  std::call_once(gOnceFlag, initializeSharedResources);

  // ... Do some work, including using the shared resources
  cout << "Processing" << endl;
}


void chap23TestThreadCallOnce()
{
  std::cout << "-----------------------" << __func__ << std::endl;
  // Launch 3 threads.
  vector<thread> threads(3);
  for (auto& t : threads) {
    t = thread{ processingFunction };
  }

  // Join on all threads
  for (auto& t : threads) {
    t.join();
  }
}


class CounterMutex
{
public:
  CounterMutex(int id, int numIterations)
    : mId(id), mNumIterations(numIterations)
  {
  }

  void operator()() const
  {
    for (int i = 0; i < mNumIterations; ++i)
    {
      lock_guard<mutex> lock(mMutex);
      cout << "Counter " << mId << " has value " << i << endl;
    }
  }

private:
  int mId;
  int mNumIterations;
  static mutex mMutex;
};

mutex CounterMutex::mMutex;

void chap23TestThreadFunctionObjectWithMutex()
{
  std::cout << "-----------------------" << __func__ << std::endl;
  // Using uniform initialization syntax
  thread t1{ CounterMutex{ 1, 20 } };

  // Using named variable
  CounterMutex c(2, 12);
  thread t2(c);

  // Using temporary
  thread t3(CounterMutex(3, 10));

  // Wait for threads to finish
  t1.join();
  t2.join();
  t3.join();
}

class CounterTimedMutex
{
public:
  CounterTimedMutex(int id, int numIterations)
    : mId(id), mNumIterations(numIterations)
  {
  }

  void operator()() const
  {
    for (int i = 0; i < mNumIterations; ++i) {
      unique_lock<timed_mutex> lock(mTimedMutex, 200ms);						// C++14
      //unique_lock<timed_mutex> lock(mTimedMutex, chrono::milliseconds(200));	// C++11

      if (lock) {
        cout << "Counter " << mId << " has value ";
        cout << i << endl;
      }
      else {
        // Lock not acquired in 200 ms
      }
    }
  }

private:
  int mId;
  int mNumIterations;
  static timed_mutex mTimedMutex;
};

timed_mutex CounterTimedMutex::mTimedMutex;

void chap23TestThreadTimedLock()
{
  std::cout << "-----------------------" << __func__ << std::endl;
  // Using uniform initialization syntax
  thread t1{ Counter{ 1, 20 } };

  // Using named variable
  Counter c(2, 12);
  thread t2(c);

  // Using temporary
  thread t3(Counter(3, 10));

  // Wait for threads to finish
  t1.join();
  t2.join();
  t3.join();
}


atomic<bool> initialized(false);
mutex mut_double_check;

void func_double_check()
{
  if (!initialized) {
    unique_lock<mutex> lock(mut_double_check);
    if (!initialized) {
      initializeSharedResources();
      initialized = true;
    }
  }
  cout << "OK" << endl;
}

void chap23TestThreadDoubleCheckedLocking()
{
  std::cout << "-----------------------" << __func__ << std::endl;
  vector<thread> threads;

  for (int i = 0; i < 5; ++i) {
    threads.push_back(thread{ func_double_check });
  }

  for (auto& t : threads) {
    t.join();
  }
}

void chap23TestFuturePackedTask()
{
  std::cout << "-----------------------" << __func__ << std::endl;
  packaged_task<int(int, int)> task([](int i1, int i2) { return i1 + i2; });
  auto fut = task.get_future();
  task(2, 3);
  int res = fut.get();
  cout << res << endl;
}


int calculate()
{
  return 123;
}

void chap23TestFutureAsynch()
{
  std::cout << "-----------------------" << __func__ << std::endl;
  auto fut = async(calculate);
  auto fut2 = async(launch::async, calculate); // create a new thread
  auto fut3 = async(launch::deferred, calculate); // use current thread

  // Do some more work...

  // Get result
  int res = fut.get();
  cout << res << endl;

  res = fut2.get();
  cout << res << endl;

  res = fut3.get();
  cout << res << endl;
}

int calculate_with_error()
{
  throw runtime_error("Exception thrown from a thread.");
}

/*******************************************************************************
* The advantage of using futures is that they automatically transport exceptions
* between threads. At the time you call get() on a future, you receive the 
* requested result, or , any exception that occurred in the thread is rethrown 
* in the thread calling get() and you can catch them using a normal try /
* catch block.
*/
void chap23TestAsynchErrorHandling()
{
  std::cout << "-----------------------" << __func__ << std::endl;
  // Use launch::async policy to force a new thread.
  auto fut = async(launch::async, calculate_with_error);

  // Get result
  try {
    int res = fut.get();
    cout << res << endl;
  }
  catch (const exception& ex) {
    cout << "Caught exception: " << ex.what() << endl;
  }
}

void logSomeMessages(int id, Logger& logger)
{
  for (int i = 0; i < 10; ++i) {
    stringstream ss;
    ss << "Log entry " << i << " from thread " << id;
    logger.log(ss.str());
  }
}

void chap23TestLogger()
{
  Logger logger;

  vector<thread> threads;

  // Create a few threads all working with the same Logger instance.
  for (int i = 0; i < 10; ++i)
  {
    threads.emplace_back(logSomeMessages, i, ref(logger));

    // The above is equivalent to:
    // threads.push_back(thread{ logSomeMessages, i, ref(logger) });
  }

  // Wait for all threads to finish.
  for (auto& t : threads) {
    t.join();
  }
}

