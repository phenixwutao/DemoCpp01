#pragma once
#include <thread>
#include <iostream>

class thread_guard
{
public:
  explicit thread_guard(std::thread& t_) : t(t_)
  {}

  ~thread_guard()
  {
    if (t.joinable()) // 1: join can only be called once, don't call twice
    {
      std::cout << "Dtor: thread_guard about to join" << std::endl;
      t.join(); // 2
    }
  }

  thread_guard(thread_guard const&) = delete; // 3
  thread_guard& operator=(thread_guard const&) = delete;

private:
  std::thread& t;
};

void chap02ThreadStart();
void chap02ThreadInvalidReference();
void chap02ThreadInvalidReferenceFix();
void chap02TestThreadGuard();
void chap02TestDaemonThreads();
void chap02TestThreadPassParameter();
void chap02TestThreadPassReference(unsigned int);
void chap02TestThreadBindFunc();
void chap02TestThreadBindFuncParameters();
