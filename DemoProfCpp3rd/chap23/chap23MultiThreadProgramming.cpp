#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <thread>
#include <exception>
#include <stdexcept>

#include "chap23MultiThreadProgramming.h"

using namespace std;


void counter(int id, int numIterations)
{
  for (int i = 0; i < numIterations; ++i)
  {
    cout << "Counter " << id << " has value ";
    cout << i << endl;
  }
}

// P748
void chap23TestThreadWithFunctionPointer()
{
  thread t1(counter, 1, 6);
  thread t2(counter, 2, 4);
  t1.join();
  t2.join();
}

class Counter
{
public:
  Counter(int id, int numIterations)
    : mId(id), mNumIterations(numIterations)
  {
  }

  void operator()() const
  {
    for (int i = 0; i < mNumIterations; ++i) {
      cout << "Counter " << mId << " has value ";
      cout << i << endl;
    }
  }

private:
  int mId;
  int mNumIterations;
};


void chap23TestThreadWithFunctionObject()
{
  cout << __func__ << endl;
  thread t1(Counter(1, 6));
  thread t2{ Counter{2,5} };
  Counter cfunc(3, 4);
  thread t3(cfunc);

  t1.join();
  t2.join();
  t3.join();
}

void chap23TestThreadWithLambda()
{
  cout << __func__ << endl;

  int id = 1;
  int wMAX = 5;
  thread t1([id, wMAX] {
    for (int i = 0; i < wMAX; ++i)
      cout << "Counter " << id << " has value " << i << endl;
  }
  );

  t1.join();
}


class Request
{
public:
  Request(int id) : mId(id) { }

  void process()
  {
    cout << "Processing request " << mId << endl;
  }

private:
  int mId;
};

void chap23TestThreadWithMemberFunction()
{
  Request req(10);
  thread t1(&Request::process, &req);
}

void doSomeWork()
{
  for (int i = 0; i < 5; ++i) {
    cout << i << endl;
  }
  cout << "Thread throwing a runtime_error exception..." << endl;
  throw runtime_error("Exception from thread");
}

void threadFunc(exception_ptr& err)
{
  try {
    doSomeWork();
  }
  catch (...) {
    cout << "Thread caught exception, returning exception..." << endl;
    err = current_exception();
  }
}

void doWorkInThread()
{
  exception_ptr error;
  // Launch background thread
  thread t{ threadFunc, ref(error) };
  // Wait for thread to finish
  t.join();
  // See if thread has thrown any exception
  if (error) {
    cout << "Main thread received exception, rethrowing it..." << endl;
    rethrow_exception(error);
  }
  else {
    cout << "Main thread did not receive any exception." << endl;
  }
}

void chap23TestThreadWithExceptions()
{
  cout << __func__ << endl;

  try {
    doWorkInThread();
  }
  catch (const exception& e) {
    cout << "Main function caught: '" << e.what() << "'" << endl;
  }
}

