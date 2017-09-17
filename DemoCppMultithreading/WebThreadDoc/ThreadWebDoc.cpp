#include "StdAfx.h"

// library headers
#include <iostream>
#include <algorithm>
#include <thread>
#include <string>
#include <vector>

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

