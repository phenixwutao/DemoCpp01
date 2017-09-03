#include "stdafx.h"

#include <iostream>
#include <thread>

#include "chap01DemoHello.h"

using namespace std;

void hello()
{
  cout << "Hello Concurrent" << endl;
}
void chap01DemoHello()
{
  thread t(hello);
  t.join();
}
