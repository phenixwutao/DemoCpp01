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
    Sleep(800); // sleep for some mini-sec
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
      Sleep(800);
      std::cout << "Display Thread operator Executing" << i << std::endl;
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
      Sleep(800);
      std::cout << "Lambda Executing" << i << std::endl;
    }
  });

  printf("3 In %s\n", __func__);
  thr_lambda.join();
}
