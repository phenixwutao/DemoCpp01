#include "stdafx.h"
#include "ProfCpp4thCh23_Multithreads.h"

#include <iostream>
#include <thread> // thread header file
using namespace std;

namespace chap23
{
  void counter01(int id, int numIterations)
  {
    for (int i = 0; i < numIterations; ++i) {
      cout << "Counter " << id << " has value " << i << endl;
    }
  }

  void chap23DemoBasicThread()
  {
    FUNC_INFO;
    thread t1(counter01, 1, 6);
    thread t2(counter01, 2, 4);

    // output is unpredictable due to two threads racing
    t1.join();
    t2.join();
  }

  class Counter02
  {
  public:
    Counter02(int id, int numIterations)
      : mId(id), mNumIterations(numIterations)
    {
    }

    void operator()() const
    {
      for (int i = 0; i < mNumIterations; ++i) {
        cout << "Counter " << mId << " has value " << i << endl;
      }
    }

  private:
    int mId;
    int mNumIterations;
  };

  void chap23DemoThreadWithFunctionObject()
  {
    FUNC_INFO;
    // Using uniform initialization syntax
    thread t1{ Counter02{ 1, 15 } };

    // Using named variable
    Counter02 c(2, 12);
    thread t2(c);

    // Using temporary
    thread t3(Counter02(3, 10));

    // Wait for threads to finish
    t1.join();
    t2.join();
    t3.join();
  }
  void chap23DemoThreadWithLambda()
  {
    FUNC_INFO;
    int id = 1;
    int numIterations = 5;
    thread t1([id, numIterations] () 
    {
      for (int i = 0; i < numIterations; ++i)
      {
        cout << "Counter " << id << " has value " << i << endl;
      }
    });

    t1.join();
  }
}
