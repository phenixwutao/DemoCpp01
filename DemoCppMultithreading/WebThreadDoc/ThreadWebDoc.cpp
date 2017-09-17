#include "StdAfx.h"

// library headers
#include <iostream>
#include <algorithm>
#include <thread>
#include <string>

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

void ThreadThreeWaysCreateThreads()
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
