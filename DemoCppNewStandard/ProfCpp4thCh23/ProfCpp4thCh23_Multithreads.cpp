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

}
