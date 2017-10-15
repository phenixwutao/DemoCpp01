#include "StdAfx.h"

#include <string>
#include <iostream>
#include <cassert>

#include <chrono>

#include "ModernCpp.h"

using namespace std;

namespace DemoExpressingTimeIntervalsWithChrono // recipe_6_01
{
  void execute()
  {
    {
      std::chrono::hours         half_day(12);
      std::chrono::minutes       half_hour(30);
      std::chrono::seconds       half_minute(30);
      std::chrono::milliseconds  half_second(500);
      std::chrono::microseconds  half_milisecond(500);
      std::chrono::nanoseconds   half_microsecond(500);
    }

    {
      using namespace std::chrono_literals;

      auto half_day = 12h;
      auto half_hour = 30min;
      auto half_minute = 30s;
      auto half_second = 500ms;
      auto half_milisecond = 500us;
      auto half_microsecond = 500ns;
    }

    {
      std::chrono::hours   half_day_in_h(12);
      std::chrono::minutes half_day_in_min(half_day_in_h);

      std::cout << half_day_in_h.count() << "h" << std::endl;
      std::cout << half_day_in_min.count() << "min" << std::endl;
    }

    {
      using namespace std::chrono_literals;

      auto total_seconds = 12345s;
      auto hours = std::chrono::duration_cast<std::chrono::hours>(total_seconds);
      auto minutes = std::chrono::duration_cast<std::chrono::minutes>(total_seconds % 1h);
      auto seconds = std::chrono::duration_cast<std::chrono::seconds>(total_seconds % 1min);

      std::cout << hours.count() << ':'
        << minutes.count() << ':'
        << seconds.count() << std::endl; // 3:25:45
    }

    {
      using namespace std::chrono_literals;

      auto total_seconds = 12345s;
      auto m1 = std::chrono::floor<std::chrono::minutes>(total_seconds); // 205 min
      auto m2 = std::chrono::round<std::chrono::minutes>(total_seconds); // 206 min
      auto m3 = std::chrono::ceil<std::chrono::minutes>(total_seconds);  // 206 min
      auto sa = std::chrono::abs(total_seconds);
    }

    {
      using namespace std::chrono_literals;

      auto d1 = 1h + 23min + 45s; // d1 = 5025s
      auto d2 = 3h + 12min + 50s; // d2 = 11570s
      cout << "d1 " << d1.count() << " s, d2 "<< d2.count() << " s" << endl;
      if (d1 < d2) {}
    }

    {
      using namespace std::chrono_literals;

      std::chrono::duration<double, std::ratio<10>> d(1.2); // 12 sec

      assert(std::chrono::duration_cast<std::chrono::seconds>(d).count() == (12s).count());
    }
  }
}

void Ch06_DemoExpressingTimeIntervalsWithChrono()
{
  FUNC_INFO;
  DemoExpressingTimeIntervalsWithChrono::execute();
}

namespace DemoMeasuringFunctionExecutionTimeWithStandardClock
{
  void func(int const count = 100000000)
  {
    for (int i = 0; i < count; ++i);
  }

  template <typename Time  = std::chrono::microseconds,
            typename Clock = std::chrono::high_resolution_clock>
  struct perf_timer
  {
    template <typename F, typename... Args>
    static Time duration(F&& f, Args... args)
    {
      auto start = Clock::now();

      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

      auto end = Clock::now();

      return std::chrono::duration_cast<Time>(end - start);
    }
  };

  template <typename T>
  void print_clock()
  {
    std::cout << "precision: " << (1000000.0 * double(T::period::num)) / (T::period::den) << std::endl;
    std::cout << "steady:    " << T::is_steady << std::endl;
  }

  void execute()
  {
    {
      auto start = std::chrono::high_resolution_clock::now();

      func();

      auto diff = std::chrono::high_resolution_clock::now() - start;

      std::cout << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
      std::cout << std::chrono::duration<double, std::nano>(diff).count() << "ns" << std::endl;
    }

    {
      auto t = perf_timer<>::duration(func, 100000000);

      std::cout << std::chrono::duration<double, std::milli>(t).count() << "ms" << std::endl;
      std::cout << std::chrono::duration<double, std::nano>(t).count() << "ns" << std::endl;
    }

    {
      auto t1 = perf_timer<std::chrono::nanoseconds>::duration(func, 100000000);
      auto t2 = perf_timer<std::chrono::microseconds>::duration(func, 100000000);
      auto t3 = perf_timer<std::chrono::milliseconds>::duration(func, 100000000);

      auto total = t1 + t2 + t3;

      std::cout << std::chrono::duration<double, std::micro>(total).count() << "us" << std::endl;
    }

    {
      print_clock<std::chrono::system_clock>();
      print_clock<std::chrono::high_resolution_clock>();
      print_clock<std::chrono::steady_clock>();
    }
  }
}

void Ch06_DemoMeasuringFunctionExecutionTimeWithStandardClock()
{
  FUNC_INFO;
  DemoMeasuringFunctionExecutionTimeWithStandardClock::execute();
}


#include <set>
#include <unordered_set>

namespace DemoGeneratingHashValues // recipe_6_03
{
  using namespace std::string_literals;

  struct Item
  {
    int         id;
    std::string name;
    double      value;

    Item(int const id, std::string const & name, double const value)
      : id(id), name(name), value(value)
    {
    }

    bool operator==(Item const & other) const
    {
      return (id == other.id &&
              name == other.name &&
              value == other.value);
    }

    bool operator!=(Item const & other) const
    {
      return !(*this == other);
    }

    bool operator<(Item const & other) const
    {
      return (id < other.id &&
              name < other.name &&
              value < other.value);
    }
  };
}

namespace std
{
  // generate hash values for user-defined class type
  template<>
  struct hash<DemoGeneratingHashValues::Item>
  {
    //typedef DemoGeneratingHashValues::Item  argument_type;
    //typedef size_t             result_type;
    using argument_type = DemoGeneratingHashValues::Item;
    using result_type = size_t;

    result_type operator()(argument_type const & item) const
    {
      result_type hashValue = 17;
      hashValue = 31 * hashValue + std::hash<int>{}(item.id);
      hashValue = 31 * hashValue + std::hash<std::string>{}(item.name);
      hashValue = 31 * hashValue + std::hash<double>{}(item.value);

      cout << hashValue << endl;
      return hashValue;
    }
  };
}

namespace DemoGeneratingHashValues
{
  void execute()
  {
    std::set<Item> set1
    {
      { 1, "one"s, 1.0 },
      { 2, "two"s, 2.0 },
      { 3, "three"s, 3.0 },
    };

    std::unordered_set<Item> set2
    {
      { 1, "one"s, 1.0 },
      { 2, "two"s, 2.0 },
      { 3, "three"s, 3.0 },
    };
    for (const auto& item : set2)
      cout << item.value << endl;
  }
}

void Ch06_DemoGeneratingHashValues()
{
  FUNC_INFO;
  DemoGeneratingHashValues::execute();
}

