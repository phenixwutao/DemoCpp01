#include <stdafx.h>
#include "Chap02List.h"

#include <iostream>
#include <thread>
#include <memory>

using std::thread;

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

  void func02(int i, const std::string & name)
  {
    printf("i=%d name %s\n", i, name.c_str());
  }
  void Chap02LT02_PassArgumentsToFunction()
  {
    std::thread t1(func02, 1, "Hayley");
    t1.join();
  }

  void func03(int & i)
  {
    i = i + 3;
    printf("in thread , i=%d\n", i);
  }

  class func04 
  {
  public:
    func04(int i) : m_i(i) {}
    void SetValue(int i) { m_i = i; }
    void printValue() { printf("m_i %d\n", m_i); }

  private:
    int m_i = 0;
  };
  void showfunc04(func04& a)
  {
    a.printValue();
  }

  void Chap02LT02_PassReferenceToDataObject()
  {
    // pass reference
    int x = 5;
    printf("before thread finish, x=%d\n", x);
    thread t(func03, std::ref(x));
    t.join();
    printf("after thread finish, x=%d\n", x);

    // pass reference of class object
    func04 a(3);
    std::thread t2(showfunc04, std::ref(a));
    t2.join();

    // invoke class method and pass class object, with class function parameter
    std::thread t3(&func04::SetValue, &a, 4);
    t3.join();
    a.printValue();
  }


  class BigObject05 {
  public:
    void process() { printf("processing Big Object\n"); }
  };
  void processBigObject05(std::unique_ptr<BigObject05> p)
  {
    p->process();
  }
  void Chap02LT02_MoveDataObject()
  {
    std::unique_ptr<BigObject05> pObj(new BigObject05);
    std::thread t(processBigObject05, std::move(pObj));
    t.join();
  }

  void some_function() {}
  void some_other_function() {}
  void Chap02LT02_MoveThread()
  {
    std::thread t1(some_function);
    std::thread t2 = std::move(t1);
    t1 = std::thread(some_other_function);
    std::thread t3;
    t3 = std::move(t2);
    //t1 = std::move(t3); // std::terminate() is called to terminate the program

    if (t1.joinable())
      t1.join();
    if (t2.joinable())
      t2.join();
    if (t3.joinable())
      t3.join();
  }
}
