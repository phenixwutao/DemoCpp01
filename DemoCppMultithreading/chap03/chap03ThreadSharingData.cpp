#include "StdAfx.h"

#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>

#include "chap03ThreadSharingData.h"

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find)
    != some_list.end();
}

void chap03TestMutexLock()
{
  add_to_list(42);
  std::cout << "contains(1)=" << list_contains(1)
    << ", contains(42)=" << list_contains(42) << std::endl;
}

/********************************
* Test unsafe share data 
********************************/
class some_data
{
  int a;
  std::string b;
public:
  void do_something()
  {}
};

class data_wrapper
{
private:
  some_data data;
  std::mutex m;
public:
  template<typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    func(data); // 1 pass mutex lock protected data
  }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
  unprotected = &protected_data;
}


void chap03TestUnsafeSharedData()
{
  data_wrapper x;
  x.process_data(malicious_function); // 2 pass a malicious function using ptotected data reference or pointer
  unprotected->do_something(); // 3 do something without mutex lock protection
}
