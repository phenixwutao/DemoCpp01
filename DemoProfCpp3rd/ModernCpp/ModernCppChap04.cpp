#include "StdAfx.h"

#include <string>
#include <iostream>
#include <type_traits>

#include "ModernCpp.h"
using std::cout;
using std::endl;

namespace DemoConditionallyCompiling
  {

#if !defined(_UNIQUE_NAME_)
#define _UNIQUE_NAME_

  class foo
    {
    };

#endif

  void show_compiler()
    {
#if defined _MSC_VER
    std::cout << "Visual C++" << std::endl;
#elif defined __clang__
    std::cout << "Clang" << std::endl;
#elif defined __GNUG__
    std::cout << "GCC" << std::endl;
#else
    std::cout << "Unknown compiler" << std::endl;
#endif
    }

  void show_compiler_version()
    {
#if defined _MSC_VER

    std::cout <<
#if (_MSC_VER >= 1900)
      "Visual C++ 2015 or newer"
#else 
      "Visual C++ " << _MSC_FULL_VER
#endif
      << std::endl;

#elif defined __clang__

    std::cout <<
#if (__clang_major__ == 3) && (__clang_minor__ >= 9)
      "Clang 3.9 or newer"
#else
      "Clang " << __clang_version__
#endif
      << std::endl;

#elif defined __GNUG__

    std::cout <<
#if __GNUC__ >= 5 && __GNUC_MINOR__ > 0
      "GCC 5.0 or newer"
#else
      "GCC " << __VERSION__
#endif
      << std::endl;

#else
    std::cout << "Unknown compiler" << std::endl;
#endif
    }

  void show_architecture()
    {
#if defined _MSC_VER

    std::cout <<
#if defined _M_X64
      "AMD64"
#elif defined _M_IX86
      "INTEL x86"
#elif defined _M_ARM
      "ARM"
#else
      "unknown"
#endif
      << std::endl;

#elif defined __clang__ || __GNUG__

    std::cout <<
#if defined __amd64__
      "AMD64"
#elif defined __i386__
      "INTEL x86"
#elif defined __arm__
      "ARM"
#else
      "unknown"
#endif
      << std::endl;

#else
#error Unknown compiler
#endif
    }

  void show_configuration()
    {
    std::cout <<
#ifdef _DEBUG
      "debug"
#else
      "release"
#endif
      << std::endl;
    }

  void execute()
    {
    show_compiler();

    show_compiler_version();

    show_architecture();

    show_configuration();
    }
  }

void Ch04_DemoConditionallyCompiling()
  {
  FUNC_INFO;
  DemoConditionallyCompiling::execute();
  }

namespace DemoPreprocessStringificationAndConcatenation
{
#define MAKE_STR2(x)    #x
#define MAKE_STR(x)     MAKE_STR2(x)

#define MERGE2(x, y)    x##y
#define MERGE(x, y)     MERGE2(x, y)

#define DECL_MAKE(x)    DECL_MAKE2(x)
#define DECL_MAKE2(x)   x* make##_##x() { return new x(); }

#define NUMBER 42

  struct bar {};
  struct foo {};

  DECL_MAKE(foo);
  DECL_MAKE(bar);

  void execute()
  {
    std::string s1{ MAKE_STR(sample) };  // s1 = "sample"
    std::string s2{ MAKE_STR2(sample) }; // s2 = "sample"

    std::string s3{ MAKE_STR(NUMBER) };    // s3 = "42"
    std::string s4{ MAKE_STR2(NUMBER) };   // s4 = "NUMBER"

    auto f = make_foo(); // f is a foo*
    auto b = make_bar(); // b is a bar*
    cout << "s1 " << s1 << endl;
    cout << "s2 " << s1 << endl;
    cout << "s3 " << s1 << endl;
    cout << "s4 " << s1 << endl;
    cout << "MERGE(1, 2) "<< MERGE(1, 2) << endl;
    cout << "f " << f << endl;
    cout << "b " << b << endl;
    if (f != nullptr)
      delete f;
    if (b != nullptr)
      delete b;
  }
}

void Ch04_DemoPreprocessStringificationAndConcatenation()
{
  FUNC_INFO;
  DemoPreprocessStringificationAndConcatenation::execute();
}


namespace DemoPerformingCompileTimeAssertionChecks
{
  struct alignas(8) item
  {
    int      id;
    bool     active;
    double   value;
  };

  template <typename T>
  class pod_wrapper
  {
    static_assert(std::is_pod<T>::value, "Error: POD type expected!");

    T value;
  };

  struct point
  {
    int x;
    int y;
  };

  template<typename T>
  auto mul(T const a, T const b)
  {
    static_assert(std::is_integral<T>::value, "Error: Integral type expected");

    return a * b;
  }

  class Info
  {
  public:
    Info() = default;
    Info(const Info&) = delete;
    Info(Info&&) = default;

    Info& operator=(const Info&) = default;
    Info& operator=(Info&&) = delete;
  };

  void execute()
  {
    pod_wrapper<int>         w1; // OK
    pod_wrapper<point>       w2; // OK
    //pod_wrapper<std::string> w3; // error: POD type expected

    auto v1 = mul(1, 2);       // OK
    //auto v2 = mul(12.0, 42.5); // error: Integral type expected

    //static_assert(std::is_copy_constructible<Info>::value, "Error: Info requires copying");
    static_assert(std::is_default_constructible<Info>::value, "Error: Info requires default-constructor");
    static_assert(std::is_move_constructible<Info>::value, "Error: Info requires default-constructor");
  }
}

#include <type_traits>

void Ch04_DemoPerformingCompileTimeAssertionChecks()
{
  FUNC_INFO;
  DemoPerformingCompileTimeAssertionChecks::execute();
}

