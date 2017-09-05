#include "StdAfx.h"

#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>
#include <stack>
#include <memory>

#include "chap03ThreadSharingData.h"
using namespace std;

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


struct empty_stack : std::exception
{
  const char* what() const throw()
  {
    return "empty stack";
  }

};

template<typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  threadsafe_stack() {}
  threadsafe_stack(const threadsafe_stack& other)
  {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  threadsafe_stack& operator=(const threadsafe_stack&) = delete;

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
  }
  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();
    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    return res;
  }

  void pop(T& value)
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();
    value = data.top();
    data.pop();
  }
  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

void chap03TestThreadsafeStack()
{
  threadsafe_stack<int> si;
  si.push(5);
  auto value = si.pop();
  cout << __func__ << " pop value : " << *(value.get()) << endl;
  if (!si.empty())
  {
    int x;
    si.pop(x);
  }
}

/************** Lock multiple mutex ********************/
class some_big_object
{
};

void swap(some_big_object& lhs, some_big_object& rhs)
{
}

class X
{
private:
  some_big_object some_detail;
  mutable std::mutex m;

public:
  X(some_big_object const& sd) :some_detail(sd) {}

  friend void swap(X& lhs, X& rhs)
  {
    if (&lhs == &rhs)
      return;
    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
    swap(lhs.some_detail, rhs.some_detail);
  }
};

/*-----------------------------------------------------------------------------*/
struct bank_account
{
  explicit bank_account(int balance) : balance(balance) {}
  int balance;
  std::mutex m;
};

/***************************************************************************
* defer_lock_t	do not acquire ownership of the mutex
* try_to_lock_t	try to acquire ownership of the mutex without blocking
* adopt_lock_t	assume the calling thread already has ownership of the mutex
****************************************************************************/
void transfer(bank_account &from, bank_account &to, int amount)
{
  // lock both mutexes without deadlock
  std::lock(from.m, to.m);

  // make sure both already-locked mutexes are unlocked at the end of scope
  std::lock_guard<std::mutex> lock1(from.m, std::adopt_lock);
  std::lock_guard<std::mutex> lock2(to.m, std::adopt_lock);

  // equivalent approach:
  //    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
  //    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
  //    std::lock(lock1, lock2);

  from.balance -= amount;
  to.balance += amount;
}

void chap03TestLockMultipleMutex()
{
  bank_account my_account(100);
  bank_account your_account(50);

  std::thread t1(transfer, std::ref(my_account), std::ref(your_account), 10);
  cout << "my_account.balance " << my_account.balance 
    << " your_account.balance " << your_account.balance << endl;

  std::thread t2(transfer, std::ref(your_account), std::ref(my_account), 5);
  cout << "my_account.balance " << my_account.balance
    << " your_account.balance " << your_account.balance << endl;

  t1.join();
  t2.join();
}
