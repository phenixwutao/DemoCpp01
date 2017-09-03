#include "stdafx.h"

#include <iostream>
#include <string>
#include <thread>
#include <exception>

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

void do_something_calc(int& i)
{
  ++i;
}

struct FuncCalc
{
  int& i;

  FuncCalc(int& i_) :i(i_) {}

  void operator()()
  {
    for (unsigned j = 0; j<1000000; ++j)
    {
      do_something_calc(i);
    }
  }
};

/*
* Call this function will crash
*/
void chap02ThreadInvalidReference()
{
  int some_local_state = 0;
  FuncCalc my_func_calc(some_local_state);
  std::thread my_thread(my_func_calc);
  my_thread.detach();
}

void do_something_in_current_thread()
{
  //throw::runtime_error("error in_current_thread!");
}

void chap02ThreadInvalidReferenceFix()
{
  int some_local_state = 0;
  FuncCalc my_func_calc(some_local_state);
  std::thread t(my_func_calc);
  try
  {
    // any exception could be thrown in the function
    do_something_in_current_thread();
  }
  catch (...)
  {
    cout << "catch exception here ... ..." << endl;
    t.join();
    throw;
  }

  // garantee reference to local varibale is valid
  t.join();
  cout << "work as normal here ... ..." << endl;
}

void chap02TestThreadGuard()
{
  int some_local_state = 0;
  FuncCalc my_func_calc(some_local_state);
  std::thread t(my_func_calc);
  thread_guard g(t);
  do_something_in_current_thread();
}

void do_background_work() {}

void chap02TestDaemonThreads()
{
  std::thread t(do_background_work);
  t.detach();
  auto fCanJoin = t.joinable();
  cout << (fCanJoin ? "Can join" : "Cannot join") << endl;
}

void PassParameter(int i, std::string const& s) {
  cout << __func__ << " " << i << " " << s << endl;
}

void chap02TestThreadPassParameter()
{
  char buffer[1024]; // 1
  sprintf_s(buffer, "%s", "test hello");
  std::thread t(PassParameter, 3, std::string(buffer)); // 2
  t.detach();
}


void update_data_for_widget(unsigned int w, string& data) // 1
{
  cout << __func__ << " " << w << " " << data << endl;
}

void chap02TestThreadPassReference(unsigned int w)
{
  string data;
  // use std::ref to pass a reference, not a copy
  std::thread t(update_data_for_widget, w, std::ref(data)); // 2

  t.join();

  // process un-updated data if not pass in by std::ref
  //process_widget_data(data); // 3
}

class FuncParam
{
public:
  void do_lengthy_work1() {}

  void do_lengthy_work2(int num) {
    cout << "do_lengthy_work2 " << num << endl;
  }
};

void chap02TestThreadBindFunc()
{
  FuncParam my_x;
  // thread function is FuncParam::do_lengthy_work1
  // address is: &my_x
  std::thread t(&FuncParam::do_lengthy_work1, &my_x); // 1
  t.join();
}

void chap02TestThreadBindFuncParameters()
{
  FuncParam my_x;
  // thread function is FuncParam::do_lengthy_work2
  // address is: &my_x
  // thread function parameter: int num
  int num = 9;
  std::thread t(&FuncParam::do_lengthy_work2, &my_x, num); // 1
  t.join();
}

