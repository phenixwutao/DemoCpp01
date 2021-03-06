#include "StdAfx.h"

#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>
#include <stack>
#include <memory>
#include <map>
#include <shared_mutex>

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
  // Either lock both, or lock none of them
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


class hierarchical_mutex
{
  std::mutex internal_mutex;
  unsigned long const hierarchy_value;
  unsigned long previous_hierarchy_value;
  static thread_local unsigned long this_thread_hierarchy_value;

  void check_for_hierarchy_violation()
  {
    if (this_thread_hierarchy_value <= hierarchy_value)
    {
      throw std::logic_error("mutex hierarchy violated");
    }
  }
  void update_hierarchy_value()
  {
    previous_hierarchy_value = this_thread_hierarchy_value;
    this_thread_hierarchy_value = hierarchy_value;
  }
public:
  explicit hierarchical_mutex(unsigned long value) :
    hierarchy_value(value),
    previous_hierarchy_value(0)
  {}
  void lock()
  {
    check_for_hierarchy_violation();
    internal_mutex.lock();
    update_hierarchy_value();
  }
  void unlock()
  {
    this_thread_hierarchy_value = previous_hierarchy_value;
    internal_mutex.unlock();
  }
  bool try_lock()
  {
    check_for_hierarchy_violation();
    if (!internal_mutex.try_lock())
      return false;
    update_hierarchy_value();
    return true;
  }
};

thread_local unsigned long
hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

void chap03TestHierarchicalMutex()
{
  hierarchical_mutex m1(42);
  hierarchical_mutex m2(2000);
}


class hierarchical_mutex_simple
{
public:
  explicit hierarchical_mutex_simple(unsigned level)
  {}

  void lock()
  {}
  void unlock()
  {}
};


hierarchical_mutex_simple high_level_mutex(10000);
hierarchical_mutex_simple low_level_mutex(5000);

int do_low_level_stuff()
{
  return 42;
}


int low_level_func()
{
  std::lock_guard<hierarchical_mutex_simple> lk(low_level_mutex);
  return do_low_level_stuff();
}

void high_level_stuff(int some_param)
{}


void high_level_func()
{
  std::lock_guard<hierarchical_mutex_simple> lk(high_level_mutex);
  high_level_stuff(low_level_func());
}

void thread_a()
{
  high_level_func();
}

hierarchical_mutex_simple other_mutex(100);
void do_other_stuff()
{}


void other_stuff()
{
  high_level_func();
  do_other_stuff();
}

void thread_b()
{
  std::lock_guard<hierarchical_mutex_simple> lk(other_mutex);
  other_stuff(); // break the rule
}

void chap03TestHierarchicalMutex2()
{
  thread t1(thread_a);
  thread t2(thread_b);
  t1.join();
  t2.join();
}


mutex owner_mutex;
void prepare_data() {}
void process_something() {}

std::unique_lock<std::mutex> get_lock()
{
  std::unique_lock<std::mutex> lk(owner_mutex);
  prepare_data();
  return lk; // 1 compiler call move constructor
}


void chap03TestMutexOwnershipTransfer()
{
  std::unique_lock<mutex> lk(get_lock()); // 2
  process_something();
}

class Y
{
private:
  int some_detail;
  mutable std::mutex m;

  int get_detail() const
  {
    std::lock_guard<std::mutex> lock_a(m); // lock once only
    return some_detail;
  }

public:
  Y(int sd) :some_detail(sd) {}

  friend bool operator==(Y const& lhs, Y const& rhs)
  {
    if (&lhs == &rhs)
      return true;
    int const lhs_value = lhs.get_detail();
    int const rhs_value = rhs.get_detail();
    return lhs_value == rhs_value;
  }
};

void chap03TestLockGranularitySingle()
{
  Y y1(1);
  Y y2(2);
  cout << __func__ << " : " << ((y1 == y2) ? "Yes" : "No") << endl;
}

std::shared_ptr<int> resource_ptr;
std::once_flag resource_flag; // 1

void init_resource()
{
  resource_ptr.reset(new int);
}

void chap03TestCallOnce()
{
  std::call_once(resource_flag, init_resource); // initialise once only
}

// call_once example
struct connection_info
{};

struct data_packet
{};

struct connection_handle
{
  void send_data(data_packet const&)
  {}
  data_packet receive_data()
  {
    return data_packet();
  }
};

struct remote_connection_manager
{
  connection_handle open(connection_info const&)
  {
    return connection_handle();
  }
} connection_manager;


/******************************************************************
* This class demo call_once for socket connection send/recv data
*******************************************************************/
class XConnection
{
private:
  connection_info   connection_details;
  connection_handle connection;
  std::once_flag    connection_init_flag;

  void open_connection()
  {
    connection = connection_manager.open(connection_details);
  }
public:
  XConnection(connection_info const& connection_details_) :
    connection_details(connection_details_)
  {}
  void send_data(data_packet const& data)
  {
    // Guarantee open_connection class methid is called once
    std::call_once(connection_init_flag, &XConnection::open_connection, this);
    connection.send_data(data);
  }
  data_packet receive_data()
  {
    // Guarantee open_connection class methid is called once
    std::call_once(connection_init_flag, &XConnection::open_connection, this);
    return connection.receive_data();
  }
};

/******************************************************************
* This class demo protect rarely-updated data structure
*******************************************************************/
class dns_entry
{};

class dns_cache
{
  std::map<std::string, dns_entry> entries;
  std::shared_mutex entry_mutex;

public:
  // use shared_lock to protect shared data for read-only access
  dns_entry find_entry(std::string const& domain)
  {
    std::shared_lock<std::shared_mutex> lk(entry_mutex);
    std::map<std::string, dns_entry>::const_iterator const it =
      entries.find(domain);
    return (it == entries.end()) ? dns_entry() : it->second;
  }

  // use lock_guard to protect shared data for write access
  void update_or_add_entry(std::string const& domain, dns_entry const& dns_details)
  {
    std::lock_guard<std::shared_mutex> lk(entry_mutex);
    entries[domain] = dns_details;
  }
};

