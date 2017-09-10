#include "stdafx.h"

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <memory>

#include "Chap04SynchronizingConcurrentOperations.h"
using namespace std;

bool flag = false;
std::mutex m;

void chap04TestWaitForEvent()
{
  unique_lock<mutex> lk(m);
  lk.unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  lk.lock();
}



struct data_chunk
{
  data_chunk() {}
  data_chunk(int id) : m_id(id){}
  int m_id = 6;
};

data_chunk prepare_data()
{
  static int id = 0;
  return data_chunk(id++);
}

void process(const data_chunk& data)
{
  cout << "processing " << data.m_id << endl;
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data_to_prepare()
{
  return data_queue.size() < 6;
}

bool is_last_chunk()
{
  return (data_queue.size() == 0);
}

void data_preparation_thread()
{
  while (more_data_to_prepare())
  {
    data_chunk const data = prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    cout << "data_preparation " << data.m_id << endl;
    data_cond.notify_one();
  }
}

void data_processing_thread()
{
  while (true)
  {
    // the waiting thread must unlock the mutex while it's waiting
    // and lock the mutex again afterward, so use unique_lock here:
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [] { return !data_queue.empty(); } );
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process(data);
    if (is_last_chunk())
      break;
  }
}

void chap04TestConditionVariables()
{
  std::thread t1(data_preparation_thread);
  std::thread t2(data_processing_thread);

  t1.join();
  t2.join();
}


template<typename T>
class threadsafe_queue
{
private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue()
  {}
  threadsafe_queue(threadsafe_queue const& other)
  {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue = other.data_queue;
  }

  size_t size()
  { 
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.size();
  }

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] {return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
    lk.unlock();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] {return !data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};


// example for a thread-safe queue
threadsafe_queue<data_chunk> safedata_queue;
data_chunk prepare_safedata()
{
  static int id = 0;
  return data_chunk(id++);
}

void safeprocess(const data_chunk& data)
{
  cout << "safeprocess " << data.m_id << endl;
}

bool more_safedata_to_prepare()
{
  return safedata_queue.size() < 6;
}

bool is_last_safechunk()
{
  return (safedata_queue.empty());
}

void safedata_preparation_thread()
{
  while (more_safedata_to_prepare())
  {
    data_chunk const data = prepare_safedata();
    safedata_queue.push(data);
    cout << "safedata_preparation " << data.m_id << endl;
  }
}

void safedata_processing_thread()
{
  while (true)
  {
    data_chunk data;
    safedata_queue.wait_and_pop(data);
    safeprocess(data);
    if (is_last_safechunk()) // break?
      break;
  }
}

void chap04TestThredasafeQueue()
{
  thread t1(safedata_preparation_thread);
  thread t2(safedata_processing_thread);
  t1.join();
  t2.join();
}

