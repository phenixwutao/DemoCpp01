#include "stdafx.h"
#include "ProfCpp4thCh23_Multithreads.h"

#include <iostream>
#include <thread> // thread header file
#include <exception>
#include <stdexcept>
#include <atomic>
#include <type_traits>
#include <vector>
#include <mutex>
#include <future>

using namespace std;

namespace chap23
{
  void counter01(int id, int numIterations)
  {
    for (int i = 0; i < numIterations; ++i) {
      cout << "Counter " << id << " has value " << i << endl;
    }
  }

  void chap23DemoBasicThread()
  {
    FUNC_INFO;
    thread t1(counter01, 1, 6);
    thread t2(counter01, 2, 4);

    // output is unpredictable due to two threads racing
    t1.join();
    t2.join();
  }

  class Counter02
  {
  public:
    Counter02(int id, int numIterations)
      : mId(id), mNumIterations(numIterations)
    {
    }

    void operator()() const
    {
      for (int i = 0; i < mNumIterations; ++i) {
        cout << "Counter " << mId << " has value " << i << endl;
      }
    }

  private:
    int mId;
    int mNumIterations;
  };

  void chap23DemoThreadWithFunctionObject()
  {
    FUNC_INFO;
    // Using uniform initialization syntax
    thread t1{ Counter02{ 1, 15 } };

    // Using named variable
    Counter02 c(2, 12);
    thread t2(c);

    // Using temporary
    thread t3(Counter02(3, 10));

    // Wait for threads to finish
    t1.join();
    t2.join();
    t3.join();
  }

  void chap23DemoThreadWithLambda()
  {
    FUNC_INFO;
    int id = 1;
    int numIterations = 5;
    thread t1([id, numIterations] () 
    {
      for (int i = 0; i < numIterations; ++i)
      {
        cout << "Counter " << id << " has value " << i << endl;
      }
    });

    t1.join();
  }

  class Request01
  {
  public:
    Request01(int id) : mId(id) { }

    void process()
    {
      cout << "Processing request " << mId << endl;
    }

  private:
    int mId;
  };

  void chap23DemoThreadWithClassMethod()
  {
    FUNC_INFO;
    Request01 req(100);
    // class method and object
    thread t { &Request01::process, &req };
    t.join();
  }

  void doSomeWork01()
  {
    for (int i = 0; i < 5; ++i) {
      cout << i << endl;
    }
    cout << "Thread throwing a runtime_error exception..." << endl;
    throw runtime_error("Exception from thread func doSomeWork01");
  }

  void threadFunc01(exception_ptr& err)
  {
    try {
      doSomeWork01();
    }
    catch (...) {
      cout << "Thread caught exception, returning exception..." << endl;
      err = current_exception();
    }
  }

  void doWorkInThread01()
  {
    exception_ptr error;

    thread t { threadFunc01, ref(error) }; // Launch thread
    t.join(); // Wait for thread to finish

    // See if thread has thrown any exception
    if (error) {
      cout << "Main thread received exception, rethrowing it..." << endl;
      rethrow_exception(error);
    }
    else {
      cout << "Main thread did not receive any exception." << endl;
    }
  }

  void chap23DemoThreadWithExceptionHandling()
  {
    FUNC_INFO;
    try {
      doWorkInThread01();
    }
    catch (const exception& e)
    {
      cout << "Main function caught: '" << e.what() << "'" << endl;
    }
  }

  class Foo1 { private: int mArray[123]; };
  class Bar1 { private: int mInt; };
  void chap23DemoIsLockFree()
  {
    FUNC_INFO;
    atomic<Foo1> f;
    cout << "Foo1 " << is_trivially_copyable_v<Foo1> << " " << f.is_lock_free() << endl;

    atomic<Bar1> b;
    cout << "Bar1 " << is_trivially_copyable_v<Bar1> << " " << b.is_lock_free() << endl;
  }

  void NonAtomicIncrement(int& counter)
  {
    for (int i = 0; i < 100; ++i)
    {
      ++counter;
      this_thread::sleep_for(1ms);
    }
  }

  void chap23DemoNonAtomicCalculation()
  {
    FUNC_INFO;
    int counter = 0;
    vector<thread> threads;

    for (int i = 0; i < 10; ++i) {
      threads.push_back( thread { NonAtomicIncrement, ref(counter) });
    }

    for (auto& t : threads) {
      t.join();
    }

    cout << "Result = " << counter << endl;
  }

  void AtomicIncrement(atomic<int>& counter)
  {
    for (int i = 0; i < 100; ++i)
    {
      ++counter;
      this_thread::sleep_for(1ms);
    }
  }

  void chap23DemoAtomicCalculation()
  {
    FUNC_INFO;
    atomic<int> counter(0);
    vector<thread> threads;

    for (int i = 0; i < 10; ++i) {
      threads.push_back( thread { AtomicIncrement, ref(counter) });
    }

    for (auto& t : threads) {
      t.join();
    }

    cout << "Result = " << counter << endl;
  }

  void OptimalIncrement(atomic<int>& counter)
  {
    int result = 0;
    for (int i = 0; i < 100; ++i) {
      ++result;
      this_thread::sleep_for(1ms);
    }
    counter += result;
  }

  void chap23DemoAtomicCalculationOptimised()
  {
    FUNC_INFO;
    atomic<int> counter(0);
    vector<thread> threads;

    for (int i = 0; i < 10; ++i) {
      threads.push_back(thread{ OptimalIncrement, ref(counter) });
    }

    for (auto& t : threads) {
      t.join();
    }

    cout << "Result = " << counter << endl;
  }

  void chap23DemoAtomicFetchAdd()
  {
    FUNC_INFO;
    atomic<int> value(10);
    cout << "Value = " << value << endl;
    int fetched = value.fetch_add(4);
    cout << "Fetched = " << fetched << endl;
    cout << "Value = " << value << endl;
  }

  void chap23DemoMutexLock()
  {
    FUNC_INFO;
    mutex mut1;
    mutex mut2;
    unique_lock<mutex> lock1(mut1, defer_lock);
    unique_lock<mutex> lock2(mut2, defer_lock);
    lock(lock1, lock2);
    // Locks acquired
  } // Locks automatically released

  void chap23DemoMutexScopedLock()
  {
    FUNC_INFO;
    mutex mut1;
    mutex mut2;
    //scoped_lock locks(mut1, mut2);
    scoped_lock<mutex, mutex> locks(mut1, mut2);

    // Locks acquired
  } // Locks automatically released


  once_flag gOnceFlag1;

  void initializeSharedResources()
  {
    // ... Initialize shared resources to be used by multiple threads.
    cout << "Shared resources initialized." << endl;
  }

  void processingFunction()
  {
    // Make sure the shared resources are initialized.
    call_once(gOnceFlag1, initializeSharedResources);

    // ... Do some work, including using the shared resources
    cout << "Processing" << endl;
  }
  void chap23DemoCallOnceResource()
  {
    FUNC_INFO;
    // Launch 3 threads
    vector<thread> threads(3);
    for (auto& t : threads)
    {
      t = thread { processingFunction };
    }

    // Join on all threads
    for (auto& t : threads)
    {
      t.join();
    }
  }

  class CounterDemo
  {
  public:
    CounterDemo(int id, int numIterations)
      : mId(id), mNumIterations(numIterations)
    {
    }

    void operator()() const
    {
      for (int i = 0; i < mNumIterations; ++i) {
        //lock_guard lock(sMutex);  // C++17
        lock_guard<mutex> lock(sMutexDemo); // the output will race without mutex lock
        cout << "Counter " << mId << " has value " << i << endl;
      }
    }

  private:
    int mId;
    int mNumIterations;
    static mutex sMutexDemo;
  };
  mutex CounterDemo::sMutexDemo;

  void chap23DemoFunctionObjectWithMutex()
  {
    FUNC_INFO;
    // Using uniform initialization syntax
    thread t1{ CounterDemo { 1, 20 } };

    // Using named variable
    CounterDemo c(2, 12);
    thread t2(c);

    // Using temporary
    thread t3(CounterDemo(3, 10));

    // Wait for threads to finish
    t1.join();
    t2.join();
    t3.join();
  }

  class TimedCounter
  {
  public:
    TimedCounter(int id, int numIterations)
      : mId(id), mNumIterations(numIterations)
    {
    }

    void operator()() const
    {
      for (int i = 0; i < mNumIterations; ++i) {
        //unique_lock lock(sTimedMutex, 200ms);  // C++17
        unique_lock<timed_mutex> lock(sTimedMutex, 200ms);
        if (lock) {
          cout << "Counter " << mId << " has value " << i << endl;
        }
        else {
          // Lock not acquired in 200ms, skip output.
        }
      }
    }

  private:
    int mId;
    int mNumIterations;
    static timed_mutex sTimedMutex;
  };

  timed_mutex TimedCounter::sTimedMutex;

  void chap23DemoFunctionObjectWithTimedMutex()
  {
    FUNC_INFO;
    // Using uniform initialization syntax
    thread t1{ TimedCounter{ 1, 20 } };

    // Using named variable
    TimedCounter c(2, 12);
    thread t2(c);

    // Using temporary
    thread t3(TimedCounter(3, 10));

    // Wait for threads to finish
    t1.join();
    t2.join();
    t3.join();
  }

  void initializeSharedResources2()
  {
    // ... Initialize shared resources to be used by multiple threads.
    cout << "Shared resources initialized." << endl;
  }

  atomic<bool> gInitialized2(false);
  mutex gMutex2;

  void processingFunction2()
  {
    if (!gInitialized2) {
      //unique_lock lock(gMutex);  // C++17
      unique_lock<mutex> lock(gMutex2);
      if (!gInitialized2) {
        initializeSharedResources2();
        gInitialized2 = true;
      }
    }
    cout << "OK" << endl;
  }

  void chap23DemoDoublyCheckedLocking()
  {
    FUNC_INFO;
    vector<thread> threads;

    for (int i = 0; i < 5; ++i)
    {
      threads.push_back(thread { processingFunction2 });
    }

    for (auto& t : threads)
    {
      t.join();
    }
  }

  void DoPromiseWork(promise<int> thePromise)
  {
    // ... Do some work ...
    // And ultimately store the result in the promise.
    thePromise.set_value(42);
  }

  void chap23DemoPromiseFuture()
  {
    FUNC_INFO;
    // Create a promise to pass to the thread.
    promise<int> myPromise;

    // Get the future of the promise.
    auto theFuture = myPromise.get_future();

    // Create a thread and move the promise into it.
    thread theThread { DoPromiseWork, std::move(myPromise) };

    // Do some more work...

    // Get the result.
    int result = theFuture.get();
    cout << "Result: " << result << endl;

    // Make sure to join the thread.
    theThread.join();
  }


  int CalculateSum(int a, int b)
  {
    return a + b;
  }

  void chap23DemoPackagedTask()
  {
    FUNC_INFO;
    // Create a packaged task to run CalculateSum.
    packaged_task<int(int, int)> task(CalculateSum);

    // Get the future for the result of the packaged task.
    auto theFuture = task.get_future();

    // Create a thread, move the packaged task into it, and
    // execute the packaged task with the given arguments.
    thread theThread{ std::move(task), 9, 3 };

    // Do some more work...

    // Get the result.
    int result = theFuture.get();
    cout << "Result: " << result << endl;

    // Make sure to join the thread.
    theThread.join();
  }

  int AsychCalcFunc()
  {
    return 123;
  }

  void chap23DemoAsychFuture()
  {
    FUNC_INFO;
    auto myFuture1 = async(AsychCalcFunc);
    auto myFuture2 = async(launch::async, AsychCalcFunc);
    auto myFuture3 = async(launch::deferred, AsychCalcFunc);

    // Do some more work...

    // Get the result.
    auto result = myFuture1.get();
    cout << "Result 1: " << result << endl;

    result = myFuture2.get();
    cout << "Result 2: " << result << endl;

    result = myFuture3.get();
    cout << "Result 3: " << result << endl;
  }

  int CalcWithError()
  {
    throw runtime_error("Exception thrown from calculate().");
  }

  void chap23DemoAsychErrorHandling()
  {
    FUNC_INFO;
    // Use the launch::async policy to force asynchronous execution.
    auto myFuture = async(launch::async, CalcWithError);

    // Do some more work...

    // Get the result.
    try {
      int result = myFuture.get();
      cout << "Result: " << result << endl;
    }
    catch (const exception& ex) {
      cout << "Caught exception: " << ex.what() << endl;
    }
  }

  void chap23DemoSharedFuture()
  {
    FUNC_INFO;
    promise<void> thread1Started, thread2Started;

    promise<int> signalPromise;
    auto signalFuture = signalPromise.get_future().share();
    //shared_future<int> signalFuture(signalPromise.get_future());

    auto function1 = [&thread1Started, signalFuture] {
      thread1Started.set_value();
      // Wait until parameter is set.
      int parameter = signalFuture.get();
      cout << "function1 " << parameter << endl;
    };

    auto function2 = [&thread2Started, signalFuture] {
      thread2Started.set_value();
      // Wait until parameter is set.
      int parameter = signalFuture.get();
      cout << "function2 " << parameter << endl;
    };

    // Run both lambda expressions asynchronously.
    // Remember to capture the future returned by async()!
    auto result1 = async(launch::async, function1);
    auto result2 = async(launch::async, function2);

    // Wait until both threads have started.
    thread1Started.get_future().wait();
    thread2Started.get_future().wait();

    // Both threads are now waiting for the parameter.
    // Set the parameter to wake up both of them.
    signalPromise.set_value(42);
  }
}
