#include "StdAfx.h"

// library headers
#include <iostream>
#include <algorithm>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <future>

// system headers
#include <windows.h>
#include <time.h>

// user defined headers
#include "ThreadWebDoc.h"

static unsigned int iPass = 0;
using namespace std;

void normal_function()
{
  for (int i = 0; i < 3; i++)
  {
    Sleep(500); // sleep for some mini-sec
    std::cout << "thread function Executing: " << i << std::endl;
  }
}

class DisplayThread
{
public:
  void operator()()
  {
    for (int i = 0; i < 3; i++)
    {
      Sleep(500);
      std::cout << "Display Thread operator Executing " << i << std::endl;
    }
  }
};

void C11ThreadThreeWaysCreateThreads()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  thread thr_function(normal_function);
  printf("1 In %s\n", __func__);
  thr_function.join();

  thread thr_func_obj { DisplayThread() };
  printf("2 In %s\n", __func__);
  thr_func_obj.join();

  thread thr_lambda([] {
    for (int i = 0; i < 3; i++)
    {
      Sleep(500);
      std::cout << "Lambda Executing " << i << std::endl;
    }
  });

  printf("3 In %s\n", __func__);
  thr_lambda.join();

  // test get thread id
  thread throbj1(normal_function);
  thread throbj2(normal_function);
  auto id1 = throbj1.get_id();
  auto id2 = throbj2.get_id();
  auto mainid = this_thread::get_id();
  printf("threads id1 vs id2 are %s\n", id1 == id2 ? "same" : "different");
  printf("threads id1 vs mainid are %s\n", id1 == mainid ? "same" : "different");
  Sleep(1600);
  throbj1.join();
  throbj2.join();
}

class WorkerThread
{
public:
  WorkerThread(unsigned short i) : _id(i) {}
  void operator()()
  {
    for (unsigned short int i = 0; i < 3; i++)
    {
      Sleep(300);
      printf("Executing WorkerThread %u\n", _id);
    }
  }
private:
  unsigned short _id = 0;
};

void C11ThreadJoinDetach()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  std::vector<std::thread> threadList;
  for (int i = 0; i < 5; i++)
  {
    threadList.push_back(std::thread(WorkerThread(i)));
  }
  // Now wait for all the worker thread to finish i.e.
  // Call join() function on each of the std::thread object
  std::cout << "wait for all the worker thread to finish" << std::endl;
  std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
  std::cout << "Exiting from Main Thread" << std::endl;

  for (const auto& item : threadList)
  {
    if (item.joinable() == true)
      printf("can join thread\n");
    else
      printf("can't join thread\n");
  }

  // ------------- test join and detach
  std::thread threadObj { WorkerThread(5) };
  if (threadObj.joinable())
  {
    std::cout << "Detaching Thread 1 " << std::endl;
    threadObj.detach();
  }
  if (threadObj.joinable())
  {
    std::cout << "Detaching Thread 2 " << std::endl;
    threadObj.detach();
  }

  std::thread threadObj2{ WorkerThread(6) };
  if (threadObj2.joinable())
  {
    std::cout << "Joining Thread 1 " << std::endl;
    threadObj2.join();
  }
  if (threadObj2.joinable())
  {
    std::cout << "Joining Thread 2 " << std::endl;
    threadObj2.join();
  }
}

class ThreadRAII
{
public:
  ThreadRAII(std::thread  & threadObj) : m_thread(threadObj)
  {

  }
  ~ThreadRAII()
  {
    // Check if thread is joinable then detach the thread
    if (m_thread.joinable())
    {
      m_thread.detach();
    }
  }
private:
  std::thread & m_thread;
};
void normal_function2()
{
  for (int i = 0; i < 3; i++)
  {
    Sleep(300);
    std::cout << "thread_function Executing: " << i << std::endl;
  }
}
void C11ThreadJoinDetachException()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  // if don't call join or detach, program will crash
  std::thread threadObj(normal_function2);

  // If we comment this Line, then program will crash
  ThreadRAII wrapperObj(threadObj);
  Sleep(1000); // wait for thread to finish, only for demo
}

void threadCallback(int x, std::string str)
{
  std::cout << "Passed Number = " << x << std::endl;
  std::cout << "Passed String = " << str << std::endl;
}

void threadCallback2(int const & x)
{
  int & y = const_cast<int &>(x);
  y++;
  std::cout << "Inside Thread x = " << x << std::endl;
}

class DummyClass {
public:
  DummyClass() {}
  DummyClass(const DummyClass & obj) {}

  void sampleMemberFunction(int x)
  {
    std::cout << "DummyClass sampleMemberFunction: " << x << std::endl;
  }
};

void C11ThreadPassingArguments()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  int x = 10;
  std::string str = "Sample String";
  // By default all arguments are copied into the internal storage of new thread.
  std::thread threadObj(threadCallback, x, str);
  threadObj.join();

  // How to pass references to thread: normal way
  int x2 = 9;
  std::cout << "In Main Thread : Before Thread Start x = " << x2 << std::endl;
  std::thread threadObj2(threadCallback2, x2);
  threadObj2.join();
  std::cout << "In Main Thread : After Thread Joins x = " << x2 << std::endl;

  // using std::ref
  int x3 = 5;
  std::cout << "In Main Thread : Before Thread Start x = " << x3 << std::endl;
  std::thread threadObj3(threadCallback2, std::ref(x3));
  threadObj3.join();
  std::cout << "In Main Thread : After Thread Joins x = " << x3 << std::endl;

  // passing arguments for class object
  DummyClass dummyObj;
  int val = 10;
  // class method; object; list of argument values
  thread thr_dummy(&DummyClass::sampleMemberFunction, &dummyObj, val);
  thr_dummy.join();
}

class Wallet
{
  int mMoney;
  std::mutex mutex;
public:
  Wallet() :mMoney(0) {}
  int getMoney() { return mMoney; }

  void addMoney(int money)
  {
    // use std::lock_guard, which is equivelant to 
    // mutex.lock();
    // mutex.unlock();

    // In constructor it locks the mutex
    std::lock_guard<std::mutex> lockGuard(mutex);
    mMoney += money;
    printf("After ad money: %d\n", mMoney);

    // Once function exits, then destructor of lock_guard Object will be called.
    // In destructor it unlocks the mutex.
  }
};

int testMultithreadedWallet()
{
  Wallet walletObject;
  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i) {
    threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
  }

  for (int i = 0; i < threads.size(); i++)
  {
    threads.at(i).join();
  }
  return walletObject.getMoney();
}

void C11ThreadShareDataMutexLock()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  int val = testMultithreadedWallet();
  if (val != 5000)
  {
    std::cout << "Error: Money in Wallet = " << val << std::endl;
  }
}


class Application
{
  std::mutex m_mutex;
  std::condition_variable m_condVar;
  bool m_bDataLoaded;

public:
  Application()
  {
    m_bDataLoaded = false;
  }
  void loadData()
  {
    // Make This Thread sleep for 1 Second
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Loading Data from XML" << std::endl;

    // Lock The Data structure
    std::lock_guard<std::mutex> guard(m_mutex);

    // Set the flag to true, means data is loaded
    m_bDataLoaded = true;

    // Notify the condition variable
    m_condVar.notify_one();
  }

  bool isDataLoaded()
  {
    return m_bDataLoaded;
  }
  
  void mainTask()
  {
    std::cout << "Do Some Handshaking" << std::endl;

    // Acquire the lock
    std::unique_lock<std::mutex> mlock(m_mutex);

    // Start waiting for the Condition Variable to get signaled
    // Wait() will internally release the lock and make the thread to block
    // As soon as condition variable get signaled, resume the thread and
    // again acquire the lock. Then check if condition is met or not
    // If condition is met then continue else again go in wait.
    m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
    std::cout << "Do Processing On loaded Data" << std::endl;
  }
};

void C11ThreadConditionVariable()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  Application app;
  std::thread thread_1(&Application::mainTask, &app);
  std::thread thread_2(&Application::loadData, &app);
  thread_2.join();
  thread_1.join();
}

void initiazer(std::promise<int> * promObj)
{
  std::cout << "Inside initiazer Thread" << std::endl;
  Sleep(2000);
  promObj->set_value(35);
}

/************************************************************************************
* std::promise is a class template and its object promises to set the value in future.
* Each std::promise object has an associated std::future object that will give the 
* value once set by the std::promise object.
* A std::promise object shares data with its associated std::future object.
*************************************************************************************/
void C11ThreadPromiseAndFuture()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  std::promise<int> promiseObj;
  std::future<int> futureObj = promiseObj.get_future();
  std::thread thr(initiazer, &promiseObj);
  std::cout << "Main thread: get "<< futureObj.get() << std::endl;
  thr.join();
}

