#include "stdafx.h"

#include <iostream>
#include <thread>

#include "chap02DemoThreadManagement.h"

using namespace std;

class background_task
{
public:
  void do_something()
  {
    cout << "do_something" << endl;
  }

  void do_something_else()
  {
    cout << "do_something_else" << endl;
  }

  void operator()()
  {
    do_something();
    do_something_else();
  }
};

void chap02ThreadStart()
{
  //// standard way of thread object
  background_task f;
  std::thread my_thread(f);
  my_thread.join();
  cout << "----------------------- 1" << endl;

  //// thread object by C++ initialization
  thread t { background_task() };
  t.join();
  cout << "----------------------- 2" << endl;


  // thread object by lambda
  thread t2( [] () {
    background_task f;
    f.do_something();
    f.do_something_else();
  });
  t2.join();
  cout << "----------------------- 3" << endl;
}

