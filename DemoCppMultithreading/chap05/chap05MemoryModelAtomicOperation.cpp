#include "StdAfx.h"

// normal headers
#include <iostream>
#include <vector>


// concurrency headers
#include <atomic>
#include <chrono>
#include <thread>


// user headers
#include "chap05MemoryModelAtomicOperation.h"

using namespace std;

std::vector<int> mydata;
std::atomic_bool data_ready(false);

void reader_thread()
{
  while (!data_ready.load())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::cout << "The answer=" << mydata[0] << "\n";
}

void writer_thread()
{
  mydata.push_back(42);
  data_ready = true;
}

void chap05TestAtomicOperation()
{
  cout << "---------------------------" << __func__ << endl;
  thread t1(reader_thread);
  thread t2(writer_thread);
  t1.join();
  t2.join();
}


