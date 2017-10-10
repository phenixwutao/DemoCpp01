#include "StdAfx.h"

#include <utility>
#include <iostream>
#include <string>

#include <numeric>
#include <vector>
#include <algorithm>
#include <functional>

#include "ModernCpp.h"


namespace DemoDefaultedAndDeletedFunctions
{
  class foo_not_copiable
  {
  public:
    foo_not_copiable() {};
  private:
    foo_not_copiable(foo_not_copiable const&);
    foo_not_copiable& operator=(foo_not_copiable const&);
  };

  class bar_not_copiable
  {
  public:
    bar_not_copiable() = default;

    bar_not_copiable(bar_not_copiable const &) = delete;
    bar_not_copiable& operator=(bar_not_copiable const&) = delete;
  };

  struct Data {};

  class data_wrapper
  {
    Data* data;
  public:
    data_wrapper(Data* d = nullptr) : data(d) {}
    ~data_wrapper() { delete data; }

    data_wrapper(data_wrapper const&) = delete;
    data_wrapper& operator=(data_wrapper const &) = delete;

    data_wrapper(data_wrapper&& o) :data(std::move(o.data))
    {
      o.data = nullptr;
    }

    data_wrapper& operator=(data_wrapper&& o)
    {
      if (this != &o)
      {
        delete data;
        data = std::move(o.data);
        o.data = nullptr;
      }

      return *this;
    }
  };

  class foo
  {
  public:
    foo() = default;

    inline foo& operator=(foo const &);
  };

  inline foo& foo::operator=(foo const &) = default;

  //void forward_declared_function();

  // ...

  //void forward_declared_function() = delete; // error

  template <typename T>
  void run(T) = delete;
  void run(long)
  {
  }

  void execute()
  {
    {
      //foo_not_copiable f1, f2;
      //foo_not_copiable f3 = f1; // error
      //f1 = f2; // error
    }

    {
      //bar_not_copiable f1, f2;
      //foo_not_copiable f3 = f1; // error
      //f1 = f2; // error         
    }

    {
      //run(42); // error: cannot be referenced, it is a deleted function
      run(42L);  // OK
    }
  }
}

void Ch03_DemoDefaultedAndDeletedFunctions()
{
  FUNC_INFO;
  DemoDefaultedAndDeletedFunctions::execute();
}

namespace DemoUsingLambdasWithStandardAlgorithms
{
  using namespace std::string_literals;

  inline bool is_positive(int const n)
  {
    return n > 0;
  }

  class range_selector
  {
    int start_;
    int end_;
  public:
    explicit range_selector(int const start, int const end) :
      start_(start), end_(end)
    {
    }

    bool operator()(int const n)
    {
      return start_ <= n && n <= end_;
    }
  };

  struct __lambda_name__
  {
    bool operator()(int const n) const { return n > 0; }
  };

  class __lambda_name_2__
  {
    int start_;
    int end_;
  public:
    explicit __lambda_name_2__(int const start, int const end) :
      start_(start), end_(end)
    {}

    __lambda_name_2__(const __lambda_name_2__&) = default;
    __lambda_name_2__(__lambda_name_2__&&) = default;
    __lambda_name_2__& operator=(const __lambda_name_2__&) = delete;
    ~__lambda_name_2__() = default;

    bool operator() (int const n) const
    {
      return start_ <= n && n <= end_;
    }
  };

  void execute()
  {
    auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
    auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };

    {
      auto positives = std::count_if(std::begin(numbers), std::end(numbers),
        is_positive);

      std::cout << "positives: " << positives << std::endl;

      auto start{ 5 }; // could be an input params
      auto end{ 10 };
      auto inrange = std::count_if(std::begin(numbers), std::end(numbers),
        range_selector(start, end));

      std::cout << "inrange(5, 10): " << inrange << std::endl;
    }

    {
      auto positives = std::count_if(std::begin(numbers), std::end(numbers),
        [](int const n) {return n > 0; });

      std::cout << "positives: " << positives << std::endl;

      auto start{ 5 };
      auto end{ 10 };
      auto inrange = std::count_if(
        std::begin(numbers), std::end(numbers),
        [start, end](int const n) {return start <= n && n <= end; });

      std::cout << "inrange(5, 10): " << inrange << std::endl;
    }

    {
      auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0,
        [](int const s, int const n) {return s + n; });

      std::cout << "sum: " << sum << std::endl;

      auto text = std::accumulate(std::begin(texts), std::end(texts), ""s,
        [](std::string const s, std::string const n) {return s + n; });

      std::cout << "text: " << text << std::endl;
    }
  }
}

void Ch03_DemoUsingLambdasWithStandardAlgorithms()
{
  FUNC_INFO;
  DemoUsingLambdasWithStandardAlgorithms::execute();
}

namespace DemoUsingGenericLambdas
{
  using namespace std::string_literals;
  using namespace std;

  struct __lambda_name__
  {
    template<typename T1, typename T2>
    auto operator()(T1 const s, T2 const n) const { return s + n; }

    __lambda_name__(const __lambda_name__&) = default;
    __lambda_name__(__lambda_name__&&) = default;
    __lambda_name__& operator=(const __lambda_name__&) = delete;
    ~__lambda_name__() = default;
  };

  void execute()
  {
    auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
    auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };

    // with non-generic lambdas
    {
      // begin,  end,  initial value, binary_operation
      auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0,
        [](int const s, int const n) {return s + n; });
      cout << sum << endl;

      auto text = std::accumulate(std::begin(texts), std::end(texts), ""s,
        [](std::string const s, std::string const n) {return s + n; });
      cout << text << endl;
    }

    // with generic lambdas
    {
      auto lsum = [](auto const s, auto const n) {return s + n; };

      auto sum = std::accumulate(std::begin(numbers), std::end(numbers),
        0, lsum);
      cout << sum << endl;

      auto text = std::accumulate(std::begin(texts), std::end(texts),
        ""s, lsum);
      cout << text << endl;
    }
  }

}


void Ch03_DemoUsingGenericLambdas()
{
  FUNC_INFO;
  DemoUsingGenericLambdas::execute();
}

namespace DemoWritingRecursiveLambda
{
  using namespace std;
  constexpr int fib(int const n)
  {
    return n <= 2 ? 1 : fib(n - 1) + fib(n - 2);
  }

  std::function<int(int const)> fib_create()
  {
    std::function<int(int const)> lfib = [&lfib](int const n)
    {
      return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2);
    };

    return lfib;
  }

  std::function<int(int const)> fib_create2()
  {
    std::function<int(int const)> f = [](int const n)
    {
      std::function<int(int const)> lfib = [&lfib](int n)
      {
        return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2);
      };
      return lfib(n);
    };

    return f;
  }

  void execute()
  {
    {
      auto f10 = fib(10);

      std::cout << "fib(10): " << f10 << std::endl;
    }

    {
      std::function<int(int const)> lfib = [&lfib](int const n)
      {
        return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2);
      };

      auto f10 = lfib(10);

      std::cout << "fib(10): " << f10 << std::endl;
    }

    {
      auto lfib = fib_create2();
      cout << "fib(10): " << lfib(10) << endl;

      // auto f10 = lfib(10); // crash
    }

    {
      auto lfib = fib_create2();

      auto f10 = lfib(10);

      std::cout << "fib(10): " << f10 << std::endl;
    }
  }
}

void Ch03_DemoWritingRecursiveLambda()
{
  FUNC_INFO;
  DemoWritingRecursiveLambda::execute();
}
