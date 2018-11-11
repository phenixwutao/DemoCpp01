#include "StdAfx.h"

#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>

#include "chap04Miltithreads.h"


template <typename index_t>
void say_hello_template(index_t id)
{
  std::cout << "template Hello from thread: " << id << std::endl;
}

void say_hello(uint64_t id)
{
  std::cout << "Hello from thread: " << id << std::endl;
}

namespace ParallelPractice
{
  void chap04HelloExample()
  {
    printf(">>>----------    calling %s ----------\n", __func__);;
    const uint64_t num_threads = 4;

    std::vector<std::thread> threads;

    for (uint64_t id = 0; id < num_threads; id++)
    {
      threads.emplace_back(std::thread(say_hello, id));
    }

    for (auto& thread : threads)
    {
      thread.join();
    }
  }
}
