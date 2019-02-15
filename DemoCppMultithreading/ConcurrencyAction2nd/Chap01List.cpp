#include <stdafx.h>
#include "Chap01List.h"

#include <iostream>
#include <thread>

namespace ConAction2nd
{
  void hello()
  {
    std::cout << "Hello Concurrent World, Concurrency Action 2nd!\n";
  }

  void Chap01LT01_Hello()
  {
    std::thread t(hello); 
    t.join();
  }
}
