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

namespace DemoConditionallyCompilingClassFunctions
{
  using namespace std::string_literals;

  template <typename T>
  void func(typename T::value_type const a)
  {
    std::cout << "func<>" << std::endl;
  }

  void func(int const a)
  {
    std::cout << "func" << std::endl;
  }

  template <typename T>
  struct some_type
  {
    using value_type = T;
  };

  template <typename T,
    typename = typename std::enable_if<std::is_pod<T>::value, T>::type>
    class pod_wrapper
  {
    T value;
  };

  template <typename T,
    typename = typename std::enable_if_t<std::is_pod<T>::value, T>>
    class pod_wrapper2
  {
    T value;
  };

  struct point
  {
    int x;
    int y;
  };

  template<typename T,
    typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    auto mul(T const a, T const b)
  {
    return a * b;
  }

  template <typename Test, typename T = void>
  using EnableIf = typename std::enable_if<Test::value, T>::type;

  template <typename Test, typename T = void>
  using DisableIf = typename std::enable_if<!Test::value, T>::type;

  template <typename T, typename = EnableIf<std::is_pod<T>>>
  class pod_wrapper3
  {
    T value;
  };

  template<typename T, typename = EnableIf<std::is_integral<T>>>
  auto mul2(T const a, T const b)
  {
    return a * b;
  }

  template <typename T>
  auto compute(T const a, T const b)
  {
    static_assert(std::is_integral<T>, "An integral type expected");
    return a + b;
  }

  template <typename T, typename = void>
  auto compute(T const a, T const b)
  {
    static_assert(!std::is_integral<T>, "A non-integral type expected");
    return a * b;
  }

  template <typename T, typename = EnableIf<std::is_integral<T>>>
  auto compute2(T const a, T const b)
  {
    return a * b;
  }

  template <typename T, typename = DisableIf<std::is_integral<T>>,
    typename = void>
    auto compute2(T const a, T const b)
  {
    return a + b;
  }

  void execute()
  {
    {
      func(42);
      func<some_type<int>>(42);
      //func("string"s); // error
    }

    {
      pod_wrapper2<int> w1;
      pod_wrapper2<point> w2;
      //pod_wrapper2<std::string> w3; // error
    }

    {
      auto v1 = mul(1, 2);     // OK
      //auto v2 = mul(1.0, 2.0); // error: no matching overloaded function found
    }

    {
      pod_wrapper3<int> w1;
      pod_wrapper3<point> w2;
      //pod_wrapper3<std::string> w3; // error
    }

    {
      auto v1 = mul2(1, 2);     // OK
      //auto v2 = mul2(1.0, 2.0); // error: no matching overloaded function found
    }

    {
      //auto v1 = compute(1, 2); // error: ambiguous call to overloaded function
      //auto v2 = compute(1.0, 2.0); // error: ambiguous call to overloaded function
    }

    {
      auto v1 = compute2(1, 2);     // v1 = 2
      auto v2 = compute2(1.0, 2.0); // v2 = 3.0
    }
  }
}

void Ch04_DemoConditionallyCompilingClassFunctionsWithEnable_if()
{
  FUNC_INFO;
  DemoConditionallyCompilingClassFunctions::execute();
}

//#define CONSTEXPR_IF_AVAILABLE 1

namespace DemoSelectingBranchesWithConstexpr
{
#ifdef CONSTEXPR_IF_AVAILABLE

  template <typename T>
  auto compute(T const a, T const b)
  {
    if (constexpr (std::is_integral<T>::value))
      return a * b;
    else
      return a + b;
  }

  namespace binary
  {
    using byte8 = unsigned char;
    using byte16 = unsigned short;
    using byte32 = unsigned int;

    namespace binary_literals
    {
      namespace binary_literals_internals
      {
        template <typename CharT, char d, char... bits>
        constexpr CharT binary_eval()
        {
          if (constexpr(sizeof...(bits) == 0))
            return static_cast<CharT>(d - '0');
          else if (constexpr(d == '0'))
            return binary_eval<CharT, bits...>();
          else if (constexpr(d == '1'))
            return static_cast<CharT>((1 << sizeof...(bits)) | binary_eval<CharT, bits...>());
        }
      }

      template<char... bits>
      constexpr byte8 operator""_b8()
      {
        static_assert(
          sizeof...(bits) <= 8,
          "binary literal b8 must be up to 8 digits long");

        return binary_literals_internals::binary_eval<byte8, bits...>();
      }

      template<char... bits>
      constexpr byte16 operator""_b16()
      {
        static_assert(
          sizeof...(bits) <= 16,
          "binary literal b16 must be up to 16 digits long");

        return binary_literals_internals::binary_eval<byte16, bits...>();
      }

      template<char... bits>
      constexpr byte32 operator""_b32()
      {
        static_assert(
          sizeof...(bits) <= 32,
          "binary literal b32 must be up to 32 digits long");

        return binary_literals_internals::binary_eval<byte32, bits...>();
      }
    }
  }
#endif CONSTEXPR_IF_AVAILABLE

  void execute()
  {
#ifdef CONSTEXPR_IF_AVAILABLE
    {
      auto v1 = compute(1, 2);
      auto v2 = compute(1.0, 2.0);
    }

    {
      using namespace binary;
      using namespace binary_literals;

      auto b1 = 1010_b8;
      auto b2 = 101010101010_b16;
      auto b3 = 010101010101010101010101_b32;
    }
#endif
  }
}

void Ch04_DemoSelectingBranchesWithConstexpr_if()
{
  FUNC_INFO;
  DemoSelectingBranchesWithConstexpr::execute();
}

#define ATTRIBUTES_AVAILABLE 1
namespace DemoProvidingMetadataToCompilerWithAttributes
{
#ifdef ATTRIBUTES_AVAILABLE
  // C++17 STD
  [[nodiscard]] int get_value1()
  {
    return 42;
  }

  // C++17 STD
  enum class[[nodiscard]] ReturnCodes{ OK, NoData, Error };

  ReturnCodes get_value2()
  {
    return ReturnCodes::OK;
  }

  struct[[nodiscard]] Item{};

  Item get_value3()
  {
    return Item{};
  }

  [[deprecated("Use func2()")]] void func()
  {
  }

  class[[deprecated]] foo
  {
  };

  double run([[maybe_unused]] int a, double b)
  {
    return 2 * b;
  }

  void option1() {}
  void option2() {}
#endif

  void execute()
  {
#ifdef ATTRIBUTES_AVAILABLE
    {
      // warning: ignoring return value of function declared with 'nodiscard' attribute
      get_value1();

      get_value2();

      get_value3();
    }

    {
      // compile warning: 'func' is deprecated : Use func2()
      //func();

      // compile warning: 'foo' is deprecated
      //foo f;
    }

    {
      run(2, 42.0);

      [[maybe_unused]] auto i = get_value1();
    }

    {
      int alternative = get_value1();
      switch (alternative)
      {
      case 1:
        option1();
        [[fallthrough]];
      case 2:
        option2();
      }
    }
#endif
  }
}

void Ch04_DemoProvidingMetadataToCompilerWithAttributes()
{
  FUNC_INFO;
  DemoProvidingMetadataToCompilerWithAttributes::execute();
}
