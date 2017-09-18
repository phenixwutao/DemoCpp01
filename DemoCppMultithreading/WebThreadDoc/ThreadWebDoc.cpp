#include "StdAfx.h"

// library headers
#include <iostream>
#include <algorithm>
#include <thread>
#include <string>
#include <vector>
#include <list>
#include <mutex>
#include <future>
#include <chrono>
#include <cassert>

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

using namespace std::chrono;
std::string fetchDataFromDB(std::string recvdData)
{
  // Make sure that function takes 2 seconds to complete
  std::this_thread::sleep_for(seconds(2));

  //Do stuff like creating DB Connection and fetching Data
  return "DB_" + recvdData;
}

std::string fetchDataFromFile(std::string recvdData)
{
  // Make sure that function takes 2 seconds to complete
  std::this_thread::sleep_for(seconds(2));

  //Do stuff like fetching Data File
  return "File_" + recvdData;
}

void C11ThreadUsingAsynchWithFunctionPointer()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  // Get Start Time
  system_clock::time_point start = system_clock::now();

  /***************************************************************************************************
  * std::async() does following things:
  * - It automatically creates a thread (Or picks from internal thread pool) and a promise object for us.
  * - Then passes the std::promise object to thread function and returns the associated std::future object.
  * - When our passed argument function exits then its value will be set in this promise object, 
  *   so eventually return value will be available in std::future object.
  ***************************************************************************************************/
  std::future<std::string> resultFromDB = std::async(std::launch::async, // policy
                                                     fetchDataFromDB,    // thread function
                                                     "Data");            // arguments

  //Fetch Data from File
  std::string fileData = fetchDataFromFile("Data");

  //Fetch Data from DB
  // Will block till data is available in future<std::string> object.
  std::string dbData = resultFromDB.get();

  // Get End Time
  auto end = system_clock::now();

  auto diff = duration_cast < std::chrono::seconds > (end - start).count();
  std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;

  //Combine The Data
  std::string data = dbData + " :: " + fileData;

  //Printing the combined Data
  std::cout << "Data = " << data << std::endl;
}

struct DataFetcher
{
  std::string operator()(std::string recvdData)
  {
    // Make sure that function takes 2 seconds to complete
    std::this_thread::sleep_for(seconds(2));
    //Do stuff like fetching Data File
    return "File_" + recvdData;
  }
};

void C11ThreadUsingAsynchWithFunctionObject()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);

  //Calling std::async with function object
  std::future<string> dataResult = std::async(std::launch::async, // policy
                                              DataFetcher(),      // functor (call function operator)
                                              "Data");            // arguments
  string strOut = dataResult.get();
  cout << "Output is: " << strOut << endl;
}

void C11ThreadUsingAsynchWithLambda()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);

  //Calling std::async with lambda
  std::future<string> dataResult = std::async(
    [](std::string recvdData)
    {
      std::this_thread::sleep_for(seconds(2));

      //Do stuff like creating DB Connection and fetching Data
      return "DB_" + recvdData;
    }, "Data"
  );

  string strOut = dataResult.get();
  cout << "Output is: " << strOut << endl;
}

// Fetch some data from DB
std::string getDataFromDatabase(std::string token)
{
  // Do some stuff to fetch the data
  std::string data = "Data fetched from DB by Filter :: " + token;
  return data;
}

void C11ThreadUsingPackagedTaskWithFunction()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);

  // Create a packaged_task<> that encapsulated the callback i.e. a function,
  // where the function signature should match the template type, e.g. std::string(std::string
  std::packaged_task<std::string(std::string)> task(getDataFromDatabase);

  // Fetch the associated future<> from packaged_task<>
  std::future<std::string> result = task.get_future();

  // Pass the packaged_task to thread to run asynchronously
  // packaged_task<> is movable but not copy-able, so need to move it to thread i.e.
  std::thread th(std::move(task), "Arg");

  // Join the thread. Its blocking and returns when thread is finished.
  th.join();

  // Fetch the result of packaged_task<> i.e. value returned by getDataFromDB()
  // get() function will block the calling thread until the callable entity returns 
  // and std::packaged_task<> set the data in its shareable state.
  std::string data = result.get();

  std::cout << data << std::endl;
}

/*
* Function Object to Fetch Data from DB
*/
struct DBDataFetcher
{
  std::string operator()(std::string token)
  {
    // Do some stuff to fetch the data
    std::string data = "Data From " + token;
    return data;
  }
};

void C11ThreadUsingPackagedTaskWithFunctionObject()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);

  // Create a packaged_task<> that encapsulated a function object
  std::packaged_task<std::string(std::string)> task(std::move(DBDataFetcher()));

  // Fetch the associated future<> from packaged_task<>
  std::future<std::string> result = task.get_future();

  // Pass the packaged_task to thread to run asynchronously
  std::thread th(std::move(task), "functor Arg");

  // Join the thread. Its blocking and returns when thread is finished.
  th.join();

  // Fetch the result of packaged_task<> i.e. value returned by getDataFromDB()
  std::string data = result.get();

  std::cout << data << std::endl;
}

void C11ThreadUsingPackagedTaskWithLambda()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);

  // Create a packaged_task<> that encapsulated a lambda function
  std::packaged_task<std::string(std::string)> task([](std::string token)
      {
        // Do some stuff to fetch the data
        std::string data = "Data From " + token;
        return data;
      });

  // Fetch the associated future<> from packaged_task<>
  std::future<std::string> result = task.get_future();

  // Pass the packaged_task to thread to run asynchronously
  std::thread th(std::move(task), "lambda Arg");

  // Join the thread. Its blocking and returns when thread is finished.
  th.join();

  // Fetch the result of packaged_task<> i.e. value returned by getDataFromDB()
  std::string data = result.get();

  std::cout << data << std::endl;
}

void threadSleep()
{
  int i = 0;
  while (i < 10)
  {
    // Print Thread ID and Counter i
    std::cout << std::this_thread::get_id() << " :: sleeping " << i++ << std::endl;

    /**********************************************
    * This duration can be from these units:
    * std::chrono::nanoseconds
    * std::chrono::microseconds
    * std::chrono::milliseconds
    * std::chrono::seconds
    * std::chrono::minutes
    * std::chrono::hours
    ***********************************************/
    // Sleep this thread for 200 MilliSeconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
void C11ThreadPutThreadSleep()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  thread th(threadSleep);
  th.join();
}

// Print Current Time
void print_time_point(std::chrono::system_clock::time_point timePoint)
{
  auto timeStamp = std::chrono::system_clock::to_time_t(timePoint);
  //std::cout << ctime(&timeStamp) << std::endl; // depreciated function ctime
  char buf[64];
  ctime_s(buf, 64, &timeStamp);
  printf("%s\n", buf);
}

void threadSleepUntil()
{
  std::cout << "Current Time :: ";
  // Print Current Time
  print_time_point(std::chrono::system_clock::now());

  // create a time point pointing to 4 second in future
  std::chrono::system_clock::time_point timePoint =
    std::chrono::system_clock::now() + std::chrono::seconds(4);

  std::cout << "Sleep Until  :: ";
  print_time_point(timePoint);


  // Sleep Till specified time point
  // Accepts std::chrono::system_clock::time_point as argument
  std::this_thread::sleep_until(timePoint);

  std::cout << "Current Time :: ";
  // Print Current Time
  print_time_point(std::chrono::system_clock::now());
}

class Task
{
public:
  void execute(std::string command)
  {
    for (int i = 0; i < 5; i++)
    {
      std::cout << __func__ << " " << command << " :: " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  }

  static void test(std::string command)
  {
    for (int i = 0; i < 5; i++)
    {
      std::cout << __func__ << " " << command << " :: " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  }
};
void C11ThreadPutSleepUntilFutureTimePoint()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  thread th(threadSleepUntil);
  th.join();
}

void C11ThreadStartByClassMemberFunction()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  // Starting thread by class non-static member function
  Task taskExec;
  thread thr(&Task::execute, taskExec, "Sample Task");
  thr.join();

  // Starting thread by class static member function
  thread thr_static(&Task::test, "Static");
  thr_static.join();
}

void C11ThreadTransferOwnershipByMove()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  thread thr_static1(&Task::test, "Static");
  thread thr_static2 = std::move(thr_static1); // transfer thread ownership

  // print thread ID before join
  cout << "main thread  ID: " << std::this_thread::get_id() << endl;
  cout << "child1 thread ID: " << thr_static1.get_id() << endl; // invalid ID 0
  cout << "child2 thread ID: " << thr_static2.get_id() << endl;

  if (thr_static1.joinable() == true)
  {
    printf("Join thr_static1\n");
    thr_static1.join();
  }
  else
    printf("Cannot join thr_static1\n");

  if (thr_static2.joinable() == true)
  {
    printf("Join thr_static2\n");
    thr_static2.join();
  }
  else
    printf("Cannot join thr_static2\n");


  if (thr_static1.joinable() == true)
  {
    printf("Join thr_static1\n");
    thr_static1.join();
  }
  else
    printf("Cannot join thr_static1\n");

  if (thr_static2.joinable() == true)
  {
    printf("Join thr_static2\n");
    thr_static2.join();
  }
  else
    printf("Cannot join thr_static2\n");

  // print thread ID after join
  cout << "main thread  ID: " <<std::this_thread::get_id() << endl;
  cout << "child1 thread ID: " << thr_static1.get_id() << endl; // invalid ID 0
  cout << "child2 thread ID: " << thr_static2.get_id() << endl; // invalid ID 0

  /**************************************************************************** 
  * How many threads ?
  * The thread library provides the suggestion for the number of threads :
  *****************************************************************************/
  std::cout << "Number of threads: " << std::thread::hardware_concurrency() << std::endl;
}

void taskRef(int i, string info)
{
  std::cout << "taskRef worker : " << i << info << endl;
}

void taskMove(int i, string& info)
{
  std::cout << "taskMove worker : " << i << info << endl;
}

void C11ThreadWithMoveSemantics()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  // vector container stores threads
  std::vector<std::thread> workers;
  string info(" ref info");
  for (int i = 0; i < 5; i++)
  {
    auto t = std::thread(taskRef, i, std::ref(info));
    workers.push_back(std::move(t));
  }

  for (int i = 0; i < 5; i++)
  {
    auto t = std::thread(taskMove, i, std::move(info));
    workers.push_back(std::move(t));
  }

  std::cout << "main thread" << endl;

  // Looping every thread via for_each
  // The 3rd argument assigns a task
  // It tells the compiler we're using lambda ([])
  // The lambda function takes its argument as a reference to a thread, t
  // Then, joins one by one, and this works like barrier
  std::for_each(workers.begin(), workers.end(), [](std::thread &t)
                {
                  assert(t.joinable());
                  t.join();
                });
}

// a global variable
std::list<int>myList;

// a global instance of std::mutex to protect global variable
std::mutex myMutex;

void addToList(int max, int interval)
{
  // the access to this function is mutually exclusive
  std::lock_guard<std::mutex> guard(myMutex);
  for (int i = 0; i < max; i++)
  {
    if ((i % interval) == 0)
      myList.push_back(i);
  }
}

void printList()
{
  // the access to this function is mutually exclusive
  std::lock_guard<std::mutex> guard(myMutex);
  std::this_thread::sleep_for(chrono::milliseconds(1000));
  cout << "print List: ";
  for (const auto& item : myList)
    cout << item << ",";
  cout << endl;
  //for (auto itr = myList.begin(), end_itr = myList.end(); itr != end_itr; ++itr) {
  //  cout << *itr << ",";
  //}
}

void C11ThreadShareMemoryLockguard()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  int max = 10;
  std::thread t1(addToList, max, 1);
  std::thread t2(addToList, max, 3);
  std::thread t3(printList);

  t1.join();
  t2.join();
  t3.join();
}

/*------------------------------------- test local storage --------------------------------------
* A thread_local object comes into existence when a thread starts and is destroyed when the thread ends. 
* Each thread has its own instance of a thread-Local object.
*------------------------------------------------------------------------------------------------*/
thread_local int globalVar = 0;
mutex mu_localStore;

void thread_Local_Test_Func(int newVal)
{
  globalVar = newVal;
  lock_guard<mutex> lock(mu_localStore);
  cout << "Value of globalVar in thread " << this_thread::get_id() << " is " << globalVar << endl;
}

void C11ThreadLocalStorage()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  globalVar = 1;
  thread t1(thread_Local_Test_Func, 5);
  thread t2(thread_Local_Test_Func, 20);
  t1.join();
  t2.join();
  cout << "Value of globalVar in MAIN thread " << this_thread::get_id() << " is " << globalVar << endl;
}
