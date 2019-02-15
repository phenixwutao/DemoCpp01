#include <stdafx.h>
#include "Chap02List.h"

#include <iostream>
#include <thread>

namespace ConAction2nd
{
  class backgroud_task01
  {
  public:
    void operator()()
    {
      printf("backgroud_task01 functor: do something\n");
    }
  };

  void task01_do()
  {
    printf("task01_do: do something\n");
  }

  void Chap02LT01_ClassFunctor()
  {
    // calling functor
    backgroud_task01 f;
    std::thread t1(f);
    t1.join();

    // use extra () to declare a thread variable
    std::thread t2((backgroud_task01()));
    t2.join();

    //uniform initialiser
    std::thread t3{ backgroud_task01() };
    t3.join();

    // using lambda expression
    std::thread t4([] {task01_do(); });
    t4.join();
  }

}
