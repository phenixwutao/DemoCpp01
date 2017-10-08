#include "StdAfx.h"

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <iomanip>

#include "ModernCpp.h"

using namespace std;

void func1()
{
  std::cout << "thread func without params" << std::endl;
}

void func2(int const i, double const d, std::string const s)
{
  std::cout << i << ", " << d << ", " << s << std::endl;
}

void func3(int & i)
{
  i *= 2;
}

inline void print_time()
{
  auto now = std::chrono::system_clock::now();
  auto stime = std::chrono::system_clock::to_time_t(now);
#pragma warning(disable : 4996)
  auto ltime = std::localtime(&stime);

  std::cout << std::put_time(ltime, "%c") << std::endl;

  // another way of get time
  time_t rawtime;
  time(&rawtime);
  tm tmp;
  auto errNum = localtime_s(&tmp, &rawtime);
  std::cout << std::put_time(&tmp, "%c") << std::endl;

}

void func4()
{
  using namespace std::chrono;

  print_time();

  std::this_thread::sleep_for(2s);

  print_time();
}

void func5()
{
  using namespace std::chrono;

  print_time();

  std::this_thread::sleep_until(
    std::chrono::system_clock::now() + 2s);

  print_time();
}

void func6(std::chrono::seconds timeout)
{
  auto now = std::chrono::system_clock::now();
  auto then = now + timeout;

  do
  {
    /*-------------------------------------------------------------------------------------
    * The calling thread yields, offering the implementation the opportunity to reschedule.
    * thread waits for other threads to advance without blocking.
    *-------------------------------------------------------------------------------------*/
    std::this_thread::yield();
  } while (std::chrono::system_clock::now() < then);
}


void Ch08_DemoWorkingWithThreads()
{
  FUNC_INFO;
  {
    PASS_INFO(1);
    std::thread t(func1);
    t.join();
  }

  {
    PASS_INFO(2);
    std::thread t([]() {
      std::cout << "thread func without params"
        << std::endl; });
    t.join();
  }

  {
    PASS_INFO(3);
    std::thread t(func2, 42, 42.0, "42");
    t.join();
  }

  {
    PASS_INFO(4);
    std::thread t(
      [](int const i, double const d, std::string const s)
        {
          std::cout << i << ", " << d << ", " << s << std::endl;
        },
      42, 42.0, "42");
    t.join();
  }

  {
    PASS_INFO(5);
    int n = 42;
    std::thread t(func3, std::ref(n));  // pass in reference
    t.join();

    std::cout << n << std::endl;
  }

  {
    PASS_INFO(6);
    int n = 42;   // pass in reference to lambda function
    std::thread t([](int & i) {i *= 2; }, std::ref(n));
    t.join();

    std::cout << n << std::endl;
  }

  {
    PASS_INFO(7);
    std::thread t(func4);
    t.join();
  }

  {
    PASS_INFO(8);
    std::thread t(func5);
    t.join();
  }

  {
    PASS_INFO(9);
    std::thread t(func6, std::chrono::seconds(2));
    t.join();

    print_time();
  }
}
