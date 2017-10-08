#include "StdAfx.h"

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

#include <limits>
#include <bitset>

#include "ModernCpp.h"

using namespace std;

class foo
{
  int x_;

public:
  foo(int const x = 0) :x_{ x } {}
  int& get() { return x_; }
};

auto proxy_get(foo& f) { return f.get(); }

decltype(auto) proxy_get2(foo& f) { return f.get(); }

struct
{
  template<typename T, typename U>
  auto operator () (T const a, U const b) const { return a + b; }
} L;


void Ch01_DemoAuto()
{
  FUNC_INFO;
  {
    auto i = 42;				              // int
    auto d = 42.5;				            // double
    auto s = "text";				          // const char*
    auto b = new char[10]{ 0 };		    // char*
    auto p = std::make_shared<int>(42);	// std::shared_ptr<int>
    auto v = { 1, 2, 3 };			      // std::initializer_list<int>
    auto l = [](char const c) {return toupper(c); }; // lambda int(char)

    if (b != nullptr)
      delete[] b;
  }

  {
    auto s = std::string{ "text" };		   // std::string
    auto v = std::vector<int>{ 1, 2, 3 };	// std::vector<int>
  }

  {
    auto v = std::vector<int>{ 1, 2, 3 };
    int size1 = v.size();	// implicit conversion, possible loss of data
    auto size2 = v.size();
    //auto size3 = int{ v.size() }; // error, narrowing conversion
  }

  {
    std::map<int, std::string> m;

    for (std::map<int, std::string>::const_iterator it = m.cbegin();
      it != m.cend();
      ++it)
    {
    }

    for (auto it = m.cbegin(); it != m.cend(); ++it)
    {
    }
  }

  {
    foo f(42);
    auto x = f.get();
    std::cout << x << std::endl; // prints 42
    x = 100;
    std::cout << f.get() << std::endl; // prints 42
  }

  {
    auto l1 = long long{ 42 }; // error

    using llong = long long;
    auto l2 = llong{ 42 };     // OK
    auto l3 = 42LL;            // OK
  }

  {
    auto f = foo{ 42 }; 
    //auto& x = proxy_get(f); // cannot convert from 'int' to 'int &'
  }

  {
    auto f = foo{ 42 };
    decltype(auto) x = proxy_get2(f);
  }

  {
    auto ladd = [](auto const a, auto const b) { return a + b; };

    auto i = ladd(40, 2);            // 42
    auto s = ladd("forty"s, "two"s); // "fortytwo"s
  }
}

// auto func1 return int type
auto func1(int const i) -> int
{
  return 2 * i;
}

auto func2(int const i)
{
  return 2 * i;
}

/*------------------demo alias -----------------*/
typedef unsigned char   byte;
typedef unsigned char * pbyte;
typedef int             array_t[10];
//typedef void(*fn)(byte, double);

template<typename T>
class foo2
{
  typedef T value_type;
};

typedef struct
{
  int value;
} bar, *pbar;

// this is OK
typedef std::vector<int> vint_t;
vint_t v;

// this is not possible
//typedef std::vector<T> vec_t;
//vec_t<int> v;

template <typename T>
using vec_t = std::vector<T>;

template <class T>
class custom_allocator { /* ... */ };

template <typename T>
using vec_t_ca = std::vector<T, custom_allocator<T>>;

void func(byte b, double d) {}

// demo new style alias
void Ch01_DemoAlias()
{
  FUNC_INFO;
  {
    using byte = unsigned char;
    using pbyte = unsigned char *;
    using array_t = int[10];
    using fn = void(byte, double);

    byte b{ 42 };
    pbyte pb = new byte[10]{ 0 };
    array_t a{ 0,1,2,3,4,5,6,7,8,9 };
    fn* f = func;
    f(1, 42.0);

    // lambda function
    auto myfunc = [](byte b, double d) {};
    myfunc(1, 42.0);
  }

  {
    vec_t<int>           vi;
    vec_t<std::string>   vs;
  }

}

/*---------------- demo initializer list -----------------*/
void func(int const a, int const b, int const c)
{
  printf("call func normal function\n");
  std::cout << a << ", " << b << ", "<< c << std::endl;
}

void func(std::initializer_list<int> const l)
{
  printf("call func with initializer_list\n");
  for (auto const & e : l)
    std::cout << e << std::endl;
}

void Ch01_DemoInitializerList()
{
  FUNC_INFO;
  {
    int a = 42;
    double b = 1.2;
    bool c = false;
  }

  {
    class foo
    {
      int a_;
    public:
      foo(int a) :a_(a) {}
    };

    foo f1 = 42;
  }

  {
    class foo
    {
      int a_;
      double b_;
    public:
      foo() :a_(0), b_(0) {}

      foo(int a, double b = 0.0) :a_(a), b_(b) {}
    };

    foo f1;           // default initialization
    foo f2(42, 1.2);
    foo f3(42);
    //foo f4();         // function declaration
  }

  {
    struct bar
    {
      int a_;
      double b_;
    };

    // uniform initlization
    bar b = { 42, 1.2 }; 
    int a[] = { 1, 2, 3, 4, 5 };
  }

  {
    class foo
    {
      int a_;
      double b_;
    public:
      foo() :a_(0), b_(0) {}

      foo(int a, double b = 0.0) :a_(a), b_(b) {}
    };

    struct bar
    {
      int a_;
      double b_;
    };

    int i { 42 };
    double d { 1.2 };
    int arr1[3] { 1, 2, 3 };
    int* arr2 = new int[3] { 1, 2, 3 };
    foo f1 {};
    foo f2 { 42, 1.2 };
    foo f3 { 42 };
    bar b { 42, 1.2 };
    std::vector<int> v { 1, 2, 3 };
    std::map<int, std::string> m { { 1, "one" },{ 2, "two" } };//uniform initlization

    if (arr2 != nullptr)
      delete[] arr2;
  }

  {
    class foo
    {
      int a_;
      int b_;
    public:
      foo() :a_(0), b_(0) {}

      foo(int a, int b = 0) :a_(a), b_(b) {}
      foo(std::initializer_list<int> l) 
      {
        printf("call foo initializer_list\n"); 
      }
    };

    // calls constructor with initializer_list<int>
    foo f { 1, 2 };
  }

  {
    // call func(std::initializer_list<int> const l)
    func( { 1,2,3 } ); // calls second overload
  }

  {
    std::vector<int> v1 { 5 };
    std::vector<int> v2 (5);
  }

  {
    //int i { 1.2 };  		// error
    double d = 47 / 13;
    //float f1 { d };  		// error
    float f2 { 47 / 13 };		// OK
  }

  {
    int i { static_cast<int>(1.2) };
    double d = 47 / 13;
    float f1 { static_cast<float>(d) };
  }

}

// Demo Non Static Member Initialization
void Ch01_DemoNonStaticMemberInitialization()
{
  FUNC_INFO;
  struct Point
  {
    double X;
    double Y;

    Point(double const x = 0.0, double const y = 0.0) : X(x), Y(y) {}
  };

  struct foo
  {
    foo() { std::cout << "default constructor" << std::endl; }
    foo(std::string const & text) { std::cout << "constructor '" << text << "'" << std::endl; }
    foo(foo const & other) { std::cout << "copy constructor" << std::endl; }
    foo(foo&& other) { std::cout << "move constructor" << std::endl; };
    foo& operator=(foo const & other) { std::cout << "assignment" << std::endl; return *this; }
    foo& operator=(foo&& other) { std::cout << "move assignment" << std::endl; return *this; }
    ~foo() { std::cout << "destructor" << std::endl; }
  };

  enum class TextVerticalAligment { Top, Middle, Bottom };
  enum class TextHorizontalAligment { Left, Center, Right };

  struct Control
  {
    const int defaultHeigh = 14;
    const int defaultWidth = 80;

    std::string text;
    TextVerticalAligment valign = TextVerticalAligment::Middle;
    TextHorizontalAligment halign = TextHorizontalAligment::Left;

    Control(std::string const & t) : text(t)
    {}
    Control(std::string const & t,
      TextVerticalAligment const va,
      TextHorizontalAligment const ha) : text(t), valign(va), halign(ha)
    {}
  };

  {
    printf("----------- assignment\n");
    struct bar
    {
      foo f;

      bar(foo const & value)
      {
        f = value;
      }
    };

    foo f;
    bar b(f);
  }

  {
    printf("----------- initialization\n");
    struct bar
    {
      foo f;

      bar(foo const & value) : f(value)
      {
      }
    };

    foo f;
    bar b(f);
  }

  {
    enum class TextFlow { LeftToRight, RightToLeft };

    struct Control
    {
      const int DefaultHeight = 20;
      const int DefaultWidth = 100;

      TextFlow textFlow = TextFlow::LeftToRight;
      std::string text;

      Control(std::string t) : text(t)
      {}
    };
  }

  {
    printf("----------- init when declared\n");
    struct bar
    {
      foo f{ "default value" };

      // when member variable is initialised in constructor initialization list, then 
      // default value initialization where variable is delcared will not happen!
      bar() : f { "constructor initializer" }
      {
      }
    };

    bar b;
  }

}

// demo alignment
void Ch01_DemoAlignment()
{
  FUNC_INFO;
  unsigned int kPass = 0;

  // size = 1, alignment = 1
  struct foo1
  {
    char a;
  };
  printf("%u) align is %llu \n", ++kPass, alignof(foo1));

  // size = 2, alignment = 1
  struct foo2
  {
    char a;
    char b;
  };
  printf("%u) align is %llu \n", ++kPass, alignof(foo2));

  // size = 8, alignment = 4
  struct foo3
  {
    char a;
    int  b;
  };
  printf("%u) align is %llu \n", ++kPass, alignof(foo3));

  struct foo3_
  {
    char a;        // 1 byte
    char _pad0[3]; // 3 bytes padding to put b on a 4-byte boundary
    int  b;        // 4 bytes
  };
  printf("%u) align is %llu \n", ++kPass, alignof(foo3_));

  struct foo4
  {
    int a;
    char b;
    float c;
    double d;
    bool e;
  };
  printf("%u) align is %llu \n", ++kPass, alignof(foo4));

  struct foo4_
  {
    int a;         // 4 bytes
    char b;        // 1 byte
    char _pad0[3]; // 3 bytes padding to put c on a 8-byte boundary 
    float c;       // 4 bytes
    char _pad1[4]; // 4 bytes padding to put d on a 8-byte boundary
    double d;      // 8 bytes
    bool e;        // 1 byte
    char _pad2[7]; // 7 bytes padding to make sizeof struct multiple of 8
  };
  printf("%u) align is %llu \n", ++kPass, alignof(foo4_));


  // test code
  {
    // the alignas specifier is applied on a class declaration
    struct alignas(4) foo
    {
      char a;
      char b;
    };
    printf("%u) customised align is %llu \n", ++kPass, alignof(foo));

    // the compiler transforms the preceding class into the following:
    struct foo_
    {
      char a;
      char b;
      char _pad0[2];
    };
    printf("%u) transformed align is %llu \n", ++kPass, alignof(foo_));
  }

  {
    struct alignas(8) foo
    {
      alignas(2) char a;
      alignas(8) int  b;
    };
    printf("%u) specify member align is %llu \n", ++kPass, alignof(foo));

    struct foo_
    {
      char a;
      char _pad0[7];
      int b;
      char _pad1[4];
    };
    printf("%u) transform member align is %llu \n", ++kPass, alignof(foo_));


    {
      // a is required to be placed in memory at a multiple of 8
      alignas(8)   int a;
      // b is required to be placed in memory at a multiple of 256
      alignas(256) long b[4];

      printf("%p\n", &a); // eg. 0000006C0D9EF908
      printf("%p\n", &b); // eg. 0000006C0D9EFA00
    }
  }
}


void Ch01_DemoScopedEnumerations()
{
  FUNC_INFO;
  enum class Status { Unknown, Created, Connected };

  enum class Codes { OK, Failure, Unknown };

  enum class Codes2 : unsigned int
  {
    OK = 0,
    Failure = 1,
    Unknown = 0xFFFF0000U
  };

  auto print_code = [](Codes2 const code) {};

  // test code
  {
    Codes code = Codes::Unknown;

    Codes c1 = Codes::OK;					      // OK
    //int c2 = Codes::Failure;   				// error
    int c3 = static_cast<int>(Codes::Failure);// OK
    printf("c3 is %d\n", c3);
  }
}

void Ch01_DemoOverride_Final_For_Virtual_Methods()
{
  FUNC_INFO;
  {
#if defined(_WIN64)
    typedef __int64 int_ptr;
#else
    typedef int int_ptr;
#endif

    class Base
    {
    public:
      virtual void foo(int_ptr const a) {}
    };

    class Derived : public Base
    {
    public:
      virtual void foo(int const a) {} //Actually not override base class function
    };
  }

  {
    class Base
    {
      virtual void foo() = 0;
      virtual void bar() {}
      virtual void foobar() = 0 {}
    };

    class Derived1 : public Base
    {
      virtual void foo() override = 0;
      virtual void bar() override {}
      virtual void foobar() override {}
    };

    class Derived2 : public Derived1
    {
      virtual void foo() override {}
    };
  }

  {
    class Base
    {
    public:
      virtual void foo() {}
      virtual void bar() {}
    };

    class Derived1 : public Base
    {
    public:
      void foo() override {} // for readability should also use the virtual keyword
      //virtual void bar(char const c) override {} // error, no Base::bar(char const)
    };

    class Derived2 : public Derived1
    {
      // prevent further function overrides in a derived class
      virtual void foo() final {}
    };

    class Derived3 : public Derived2
    {
      //virtual void foo() override {} // error
    };

    // prevent further derivations of the class
    class Derived4 final : public Derived1
    {
      virtual void foo() override {}
    };

    //class Derived5 : public Derived4 // error
    //{
    //};
  }

  {
    // both override and final are not reserved keywords
    class foo
    {
      int final = 0;
      void override() {}
    };
  }

}

std::vector<int> getRates()
{
  return std::vector<int> {1, 1, 2, 3, 5, 8, 13};
}

void print_rate(int const rate)
{
  std::cout << rate << std::endl;
}

std::multimap<int, bool> getRates2()
{
  return std::multimap<int, bool>
  {
    { 1, true },
    { 1, true },
    { 2, false },
    { 3, true },
    { 5, true },
    { 8, false },
    { 13, true }
  };
}

void Ch01_DemoRangeBasedForLoop()
{
  FUNC_INFO;
  {
    auto rates = getRates();

    PASS_INFO(1);
    // using iterators
    for (auto it = rates.begin(); it != rates.end(); ++it)
    {
      std::cout << *it << std::endl;
    }

    PASS_INFO(2);
    // using an index
    for (size_t i = 0; i < rates.size(); ++i)
    {
      std::cout << rates[i] << std::endl;
    }
  }

  {
    auto rates = getRates();

    PASS_INFO(3);
    std::for_each(rates.begin(), rates.end(), print_rate);

    PASS_INFO(4);
    // using lambda expression
    std::for_each(rates.begin(), rates.end(), 
      [](auto const rate) { std::cout << rate << std::endl; }
    );
  }

  {
    PASS_INFO(5);
    auto rates = getRates();
    for (int rate : rates)
    {
      std::cout << rate << std::endl;
    }

    for (int& rate : rates)
    {
      rate *= 2;
    }

    PASS_INFO(6);
    for (auto&& rate : getRates())
    {
      std::cout << rate << std::endl;
    }

    for (auto & rate : rates)
    {
      rate *= 2;
    }

    PASS_INFO(7);
    for (auto const & rate : rates)
    {
      std::cout << rate << std::endl;
    }
  }

  {
    PASS_INFO(8);
    for (auto&& kvp : getRates2())
    {
      std::cout << kvp.first << std::endl;
    }

    PASS_INFO(9);
    for (auto&& kvp : getRates2())
    {
      bool flag;
      int rate;
      std::tie(rate, flag) = kvp;

      std::cout << rate << std::endl;
    }

    // C++17 STD only
#ifdef DECOMPOSITION_AVAILABLE 
    for (auto&&[rate, flag] : getRates())
    {
      std::cout << rate << std::endl;
    }
#endif
  }
}


namespace
{
  template <typename T, size_t const Size>
  class dummy_array
  {
    T data[Size] = {};

  public:
    T const & GetAt(size_t const index) const
    {
      if (index < Size) return data[index];
      throw std::out_of_range("index out of range");
    }

    void SetAt(size_t const index, T const & value)
    {
      if (index < Size) data[index] = value;
      else throw std::out_of_range("index out of range");
    }

    size_t GetSize() const { return Size; }
  };

  template <typename T, typename C, size_t const Size>
  class dummy_array_iterator_type
  {
  public:
    dummy_array_iterator_type(C& collection, size_t const index) :
      index(index),
      collection(collection)
    {
    }

    bool operator!= (dummy_array_iterator_type const & other) const
    {
      return index != other.index;
    }

    T const & operator* () const
    {
      return collection.GetAt(index);
    }

    dummy_array_iterator_type const & operator++ ()
    {
      ++index;
      return *this;
    }

  private:
    size_t   index;
    C&       collection;
  };

  template <typename T, size_t const Size>
  using dummy_array_iterator = dummy_array_iterator_type<T, dummy_array<T, Size>, Size>;

  template <typename T, size_t const Size>
  using dummy_array_const_iterator = dummy_array_iterator_type<T, dummy_array<T, Size> const, Size>;

  template <typename T, size_t const Size>
  inline dummy_array_iterator<T, Size> begin(dummy_array<T, Size>& collection)
  {
    return dummy_array_iterator<T, Size>(collection, 0);
  }

  template <typename T, size_t const Size>
  inline dummy_array_iterator<T, Size> end(dummy_array<T, Size>& collection)
  {
    return dummy_array_iterator<T, Size>(collection, collection.GetSize());
  }

  template <typename T, size_t const Size>
  inline dummy_array_const_iterator<T, Size> begin(dummy_array<T, Size> const & collection)
  {
    return dummy_array_const_iterator<T, Size>(collection, 0);
  }

  template <typename T, size_t const Size>
  inline dummy_array_const_iterator<T, Size> end(dummy_array<T, Size> const & collection)
  {
    return dummy_array_const_iterator<T, Size>(collection, collection.GetSize());
  }

  template <typename T, const size_t Size>
  void print_dummy_array(dummy_array<T, Size> const & arr)
  {
    for (auto && e : arr)
    {
      std::cout << e << std::endl;
    }
  }
}

// demo Enabling Range-Based For Loop for Custom Types
void Ch01_DemoEnableRangeBasedForLoop4CustomTypes()
{
  FUNC_INFO;
  dummy_array<int, 3> arr;
  arr.SetAt(0, 1);
  arr.SetAt(1, 2);
  arr.SetAt(2, 3);

  for (auto&& e : arr)
  {
    std::cout << e << std::endl;
  }

  print_dummy_array(arr);
}


void Ch01_DemoCheckModules()
{
  FUNC_INFO;
#define MODULE_ID_DEAL    1
#define MODULE_ID_INSTR   2
#define MODULE_ID_NL      3
#define MODULE_ID_ACCOUNT 4

#define MODULE_VALUE_DEAL    0x00000001
#define MODULE_VALUE_INSTR   0x00000002
#define MODULE_VALUE_NL      0x00000004
#define MODULE_VALUE_ACCOUNT 0x00000008

  const string kModuleDeal = "deals";
  const string kModuleInstruction = "instructions";
  const string kModuleNominalLedger = "nominalledger";
  const string kModuleAccount = "accounts";

  struct ModuleInfo
  {
    string name;
    unsigned long long value;
  };

  map<int, ModuleInfo> my_modules;
  my_modules[MODULE_ID_DEAL] = { kModuleDeal, MODULE_VALUE_DEAL };
  my_modules[MODULE_ID_INSTR] = { kModuleInstruction, MODULE_VALUE_INSTR };
  my_modules[MODULE_ID_NL] = { kModuleNominalLedger, MODULE_VALUE_NL };
  my_modules[MODULE_ID_ACCOUNT] = { kModuleAccount, MODULE_VALUE_ACCOUNT };

  for (auto& item : my_modules)
  {
    cout << "ID " << item.first << ", name '" << item.second.name << "', value " << item.second.value << endl;
  }
  string sModule = "instructions";
  for(auto& item : my_modules)
  {
    if (item.second.name == sModule)
    {
      cout << "found ID " << item.first << ", name '" << item.second.name << "', value " << item.second.value << endl;
      break;
    }
  }

  unsigned int kID = 3;
  auto it = my_modules.find(kID);
  if (it != my_modules.end())
  {
    cout << "found ID " << it->first << ", name '" << it->second.name << "', value " << it->second.value << endl;
  }
}

void Ch01_DemoExplicitConstructorAndConversionOperator()
{
  FUNC_INFO;

  struct foo
  {
    foo() { std::cout << "foo" << std::endl; }
    foo(int const a) { std::cout << "foo(a)" << std::endl; }
    foo(int const a, double const b) { std::cout << "foo(a, b)" << std::endl; }

    operator bool() const { return true; }
  };

  struct foo2
  {
    foo2() { std::cout << "foo2" << std::endl; }
    foo2(std::initializer_list<int> l) { std::cout << "foo2(list)" << std::endl; }
    foo2(int const a) { std::cout << "foo2(a)" << std::endl; }
    foo2(int const a, double const b) { std::cout << "foo2(a, b)" << std::endl; }

    operator bool() const { return true; }
  };

  //void bar(foo const f)
  //{
  //}

  enum ItemSizes { DefaultHeight, Large, MaxSize };

  class string_buffer
  {
  public:
    explicit string_buffer()
    {}

    explicit string_buffer(size_t const size)
    {}

    explicit string_buffer(char const * const ptr)
    {}

    explicit operator bool() const { return true; }
    explicit operator char * const () const { return nullptr; }
  };

  struct handle_t
  {
    explicit handle_t(int const h) : handle(h) {}

    explicit operator bool() const { return handle != 0; };
  private:
    int handle;
  };

  // test code
  {
    PASS_INFO(1); foo f1;              // foo
    PASS_INFO(2); foo f2{};            // foo

    PASS_INFO(3); foo f3(1);           // foo(a)
    PASS_INFO(4); foo f4 = 1;          // foo(a)
    PASS_INFO(5); foo f5{ 1 };         // foo(a)
    PASS_INFO(6); foo f6 = { 1 };      // foo(a)

    PASS_INFO(7); foo f7(1, 2.0);      // foo(a, b)
    PASS_INFO(8); foo f8{ 1, 2.0 };    // foo(a, b)
    PASS_INFO(9); foo f9 = { 1, 2.0 }; // foo(a, b)

    bool flag = f1;
    if (f2) {}
    PASS_INFO(10);
    std::cout << f3 + f4 << std::endl;
    if (f5 == f6) {}
  }

  {
    auto bar = [](foo const f) {};
    PASS_INFO(11); bar({});             // foo()
    PASS_INFO(12); bar(1);              // foo(a)
    PASS_INFO(13); bar({ 1, 2.0 });     // foo(a, b)
  }

  {
    string_buffer b4 = string_buffer('a');
    string_buffer b5 = static_cast<string_buffer>(ItemSizes::MaxSize);
    string_buffer b6 = string_buffer{ "a" };

    string_buffer b7{ 'a' };
    string_buffer b8('a');

    // error
    //std::cout << b4 + b5 << std::endl;
    //if (b4 == b5) {}

    std::cout << static_cast<bool>(b4) + static_cast<bool>(b5) << std::endl;
    if (static_cast<bool>(b4) == static_cast<bool>(b5)) {}
  }

  {
    auto h = handle_t{ 42 };
    bool ok = static_cast<bool>(h);
    if (h) {
    }
  }
}

namespace
{
  void print(std::string message)
  {
    std::cout << "[file1] " << message << std::endl;
  }
}

namespace
{
  template <int const& Size>
  class test { };
  int Size2 = 10;
}

void Ch01_DemoNamespace()
{
  using namespace std::string_literals;
  FUNC_INFO;
  print("run"s); // using string ""s operator


  static int Size1 = 10;


  //test<Size1> t1; // error, Size1 has internal linkage
  test<Size2> t2;

}

// ---------------------------- test inline namespace ---------------------------------
#define LIB_VERSION_2
namespace modernlib
{
#ifndef LIB_VERSION_2
  inline namespace version_1
  {
    template<typename T>
    int test(T value) { return 1; }
  }
#endif

#ifdef LIB_VERSION_2
  inline namespace version_2
  {
    template<typename T>
    int test(T value) { return 2; }
  }
#endif
}

namespace client
{
  struct foo { int a; };

}
namespace modernlib
{
  template<>
  int test(client::foo value) { return value.a; }
}

namespace client
{
  void execute()
  {
    auto y = modernlib::test(foo{ 42 });
    printf("y=%d\n",y);
  }
}

void Ch01_DemoNamespacesForSymbolVersioning()
{
  FUNC_INFO;
  client::execute();
}

std::tuple<int, std::string, double> find()
{
  return std::make_tuple(1, "marius", 1234.5);
}

void Ch01_DemoStructuredBindings()
{
  FUNC_INFO;
  {
    std::map<int, std::string> m;

    auto result = m.insert({ 1, "one" });
    std::cout << "inserted = " << result.second << std::endl
      << "value = " << result.first->second << std::endl;
  }

  {
    std::map<int, std::string> m;
    std::map<int, std::string>::iterator it;
    bool inserted;

    // pair<iterator,bool> insert (const value_type& val);
    std::tie(it, inserted) = m.insert({ 1, "one" });
    std::cout << "inserted = " << inserted << std::endl
      << "value = " << it->second << std::endl;

    std::tie(it, inserted) = m.insert({ 1, "two" });
    std::cout << "inserted = " << inserted << std::endl
      << "value = " << it->second << std::endl;
  }

  {
    int id;
    std::string name;
    double score;

    std::tie(id, name, score) = find();

    std::cout << "id=" << id
      << " name=" << name
      << " score=" << score << std::endl;
  }

  // C++17 only
#ifdef STRUCTURED_BINDINGS
  {
    std::map<int, std::string> m;
    if (auto[it, inserted] = m.insert({ 1, "two" }); inserted)
    {
      std::cout << it->second << std::endl;
    }

    {
      auto[it, inserted] = m.insert({ 1, "one" });
      std::cout << "inserted = " << inserted << std::endl
        << "value = " << it->second << std::endl;
    }

    {
      auto[it, inserted] = m.insert({ 1, "two" });
      std::cout << "inserted = " << inserted << std::endl
        << "value = " << it->second << std::endl;
    }

    auto[id, name, score] = find();

    if (auto[id, name, score] = find(); score > 1000)
    {
      std::cout << name << std::endl;
    }
  }
#endif

}

void Ch02_DemoConvertingNumericStringTypes()
{
  FUNC_INFO;
  auto si = std::to_string(42);       // si="42"
  auto sl = std::to_string(42l);      // sl="42"
  auto su = std::to_string(42u);      // su="42"
  auto sd = std::to_string(42.0);     // sd="42.000000"
  auto sld = std::to_string(42.0l);   // sld="42.000000"

  auto i1 = std::stoi("42");
  auto i2 = std::stoi("   42");
  auto i3 = std::stoi("   42fortytwo");
  auto i4 = std::stoi("+42");
  auto i5 = std::stoi("-42");

  auto i6 = std::stoi("052", nullptr, 8);
  auto i7 = std::stoi("052", nullptr, 0);
  auto i8 = std::stoi("0x2A", nullptr, 16);
  auto i9 = std::stoi("0x2A", nullptr, 0);
  auto i10 = std::stoi("101010", nullptr, 2);
  auto i11 = std::stoi("22", nullptr, 20);
  auto i12 = std::stoi("-22", nullptr, 20);

  auto pos = size_t{ 0 };
  auto i13 = std::stoi("42", &pos);      // pos = 2
  auto i14 = std::stoi("-42", &pos);     // pos = 3
  auto i15 = std::stoi("  +42dec", &pos);// pos = 5

  try
  {
    auto i16 = std::stoi("");
  }
  catch (std::exception const & e)
  {
    // prints "invalid stoi argument"
    std::cout << e.what() << std::endl;
  }

  try
  {
    auto i17 = std::stoll("12345678901234");  // OK
    auto i18 = std::stoi("12345678901234");   // throws std::out_of_range
  }
  catch (std::exception const & e)
  {
    // prints stoi argument out of range
    std::cout << e.what() << std::endl;
  }

  auto d1 = std::stod("123.45");         // d1 =  123.45000000000000
  auto d2 = std::stod("+123.45");        // d2 =  123.45000000000000
  auto d3 = std::stod("-123.45");        // d3 = -123.45000000000000
  auto d4 = std::stod("  123.45");       // d4 =  123.45000000000000
  auto d5 = std::stod("  -123.45abc");   // d5 = -123.45000000000000
  auto d6 = std::stod("1.2345e+2");      // d6 =  123.45000000000000
  auto d7 = std::stod("0xF.6E6666p3");   // d7 =  123.44999980926514

  auto d8 = std::stod("INF");            // d8 = inf
  auto d9 = std::stod("-infinity");      // d9 = -inf
  auto d10 = std::stod("NAN");           // d10 = nan
  auto d11 = std::stod("-nanabc");       // d11 = -nan

}

namespace
{
  int minimum(int const * const start, int const * const end)
  {
    int minval = INT_MAX;
    for (int const * p = start; p != end; ++p)
    {
      if (*p < minval)
        minval = *p;
    }
    return minval;
  }

  template<typename T, typename I>
  T minimum(I const start, I const end)
  {
    T minval = std::numeric_limits<T>::max();
    for (auto i = start; i < end; ++i)
    {
      if (*i < minval)
        minval = *i;
    }
    return minval;
  }

  template <typename T>
  void print_type_properties()
  {
    std::cout
      << "min=" << std::numeric_limits<T>::min() << std::endl
      << "max=" << std::numeric_limits<T>::max() << std::endl
      << "bits=" << std::numeric_limits<T>::digits << std::endl
      << "decdigits=" << std::numeric_limits<T>::digits10 << std::endl
      << "integral=" << std::numeric_limits<T>::is_integer << std::endl
      << "signed=" << std::numeric_limits<T>::is_signed << std::endl
      << "exact=" << std::numeric_limits<T>::is_exact << std::endl
      << "infinity=" << std::numeric_limits<T>::has_infinity << std::endl;
  }

  int get_value()
  {
    return 0;
  }
}

void Ch02_DemoNumberLimitsOtherProperties()
{
  FUNC_INFO;
  PASS_INFO(1);
  print_type_properties<unsigned short>();

  PASS_INFO(2);
  print_type_properties<double>();

  PASS_INFO(3);
  print_type_properties<int>();

  int range[std::numeric_limits<char>::max() + 1] = { 0 };

  switch (get_value())
  {
  case std::numeric_limits<int>::min():
    break;
  }

  auto n = 42;
  std::bitset<std::numeric_limits<decltype(n)>::digits> bits{ static_cast<unsigned long long>(n) };
}

// headers for random numbers
#include <functional>
#include <iomanip>
#include <random>
#include <chrono>

void generate_and_print(std::function<int(void)> gen, int const iterations = 10000)
{
  // map to store the numbers and  their repetition
  auto data = std::map<int, int>{};

  // generate random numbers
  for (auto n = 0; n < iterations; ++n)
    ++data[gen()];

  // find the element with the most repetitions
  auto max = std::max_element(
    std::begin(data), std::end(data),
    [](auto kvp1, auto kvp2) {return kvp1.second < kvp2.second; });

  // print the bars
  for (auto i = max->second / 200; i > 0; --i)
  {
    for (auto kvp : data)
    {
      std::cout
        << std::fixed << std::setprecision(1) << std::setw(3)
        << (kvp.second / 200 >= i ? (char)219 : ' ');
    }

    std::cout << std::endl;
  }

  // print the numbers
  for (auto kvp : data)
  {
    std::cout
      << std::fixed << std::setprecision(1) << std::setw(3)
      << kvp.first;
  }

  std::cout << std::endl;
}

void Ch02_DemoGeneratingPseudoRandomNumbers()
{
  FUNC_INFO;
  {
    PASS_INFO(1);
    auto mtgen = std::mt19937{};

    for (auto i = 0; i < 10; ++i)
    {
      std::cout << mtgen() << std::endl;
    }
  }

  {
    PASS_INFO(2);
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto mtgen = std::mt19937{ static_cast<unsigned int>(seed) };

    for (auto i = 0; i < 10; ++i)
    {
      std::cout << mtgen() << std::endl;
    }
  }

  {
    PASS_INFO(3);
    std::random_device rd;
    auto mtgen = std::mt19937{ rd() };

    for (auto i = 0; i < 10; ++i)
    {
      std::cout << mtgen() << std::endl;
    }
  }

  {
    PASS_INFO(4);
    std::random_device rd{};
    auto mtgen = std::mt19937{ rd() };
    auto ud = std::uniform_int_distribution<>{ 1, 6 };

    generate_and_print(
      [&mtgen, &ud]() {return ud(mtgen); });
  }

  {
    PASS_INFO(5);
    std::random_device rd{};
    auto mtgen = std::mt19937{ rd() };
    auto nd = std::normal_distribution<>{ 5, 2 };

    generate_and_print(
      [&mtgen, &nd]() {return static_cast<int>(std::round(nd(mtgen))); });
  }

  // set seed for random generator
  {
    PASS_INFO(6);
    time_t T;
    auto currtime = time(&T);
    srand(currtime);
    for (int i = 0; i < 50; i++)
    {
      auto wNum = rand();
      cout << wNum % 3 << " ";
      if (((i+1) % 10) == 0)
        cout << endl;
    }
  }
}

#include <array>

void Ch02_DemoMonteCarloSimulation()
{
  FUNC_INFO;
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::random_device rd;

  std::generate(std::begin(seed_data), std::begin(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  auto eng = std::mt19937{ seq };
  auto dist = std::uniform_real_distribution<>{ 0, 1 };

  auto const Simulations = 100;
  auto const Samples = 50000;

  for (auto j = 0; j < Simulations; j++)
  {
    auto hit = 0;
    auto x = 0.0;
    auto y = 0.0;

    for (auto i = 0; i < Samples; i++)
    {
      x = dist(eng);
      y = dist(eng);

      if (y <= std::sqrt(1 - std::pow(x, 2))) hit += 1;
    }

    std::cout << "" << 4.0 * hit / Samples << std::endl;
  }
}

void Ch02_DemoStandardLiteralOperators()
{
  FUNC_INFO;
  using namespace std::string_literals;

  {
    auto filename{ "C:\\Users\\Marius\\Documents\\"s };

    auto pattern{ "(\\w+)=(\\d+)$"s };

    auto sqlselect{
      "SELECT *\n\
FROM Books\n\
WHERE Publisher=\'Paktpub\'\n\
ORDER BY PubDate DESC"s };
    PASS_INFO(1);
    cout << filename << endl;
    cout << pattern << endl;
    cout << sqlselect << endl;
  }

  {
    auto filename{ R"(C:\Users\Marius\Documents\)"s };

    auto pattern{ R"((\w+)=(\d+)$)"s };

    auto sqlselect{
      R"(SELECT *
FROM Books
WHERE Publisher='Paktpub'
ORDER BY PubDate DESC)"s };
    PASS_INFO(2);
    cout << filename << endl;
    cout << pattern << endl;
    cout << sqlselect << endl;
  }

  {
    auto filename1{ R"(C:\Users\Marius\Documents\)"s };
    auto filename2{ R"(C:\\Users\\Marius\\Documents\\)"s };

    PASS_INFO(3);
    // prints C:\Users\Marius\Documents\ 
    std::cout << filename1 << std::endl;

    // prints C:\\Users\\Marius\\Documents\\ 
    std::cout << filename2 << std::endl;

    auto text{ R"!!(This text contains both "( and )".)!!"s };
    std::cout << text << std::endl;
  }

  {
    auto t1{ LR"(text)" };	// const wchar_t*
    auto t2{ u8R"(text)" };	// const char*
    auto t3{ uR"(text)" };	// const char16_t*
    auto t4{ UR"(text)" };	// const char32_t*

    auto t5{ LR"(text)"s }; // wstring
    auto t6{ u8R"(text)"s };// string
    auto t7{ uR"(text)"s }; // u16string
    auto t8{ UR"(text)"s }; // u32string
    PASS_INFO(4);
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;
    cout << t4 << endl;
    cout << t5.c_str() << endl;
    cout << t6 << endl;
    cout << t7.c_str() << endl;
    cout << t8.c_str() << endl;
  }
  printf("End\n");
}

/*------------------------ demo Creating cooked user-defined literals------------------------*/
namespace compunits
{
  constexpr size_t operator "" _KB(unsigned long long const size)
  {
    return static_cast<size_t>(size * 1024);
  }
}

void examples_kb()
{
  using namespace compunits;

  auto size{ 4_KB };         // size_t

  using byte = unsigned char;
  auto buffer = std::array<byte, 1_KB>{}; // std::array<unsigned char, 1024>
}

namespace units
{
  enum class unit
  {
    kilogram,
    liter,
    meter,
    piece,
  };

  template <unit U>
  class quantity
  {
    const double amount;
  public:
    constexpr explicit quantity(double const a) : amount(a) {}

    explicit operator double() const { return amount; }
  };

  template <unit U>
  constexpr quantity<U> operator+(quantity<U> const &q1, quantity<U> const &q2)
  {
    return quantity<U>(static_cast<double>(q1) + static_cast<double>(q2));
  }

  template <unit U>
  constexpr quantity<U> operator-(quantity<U> const &q1, quantity<U> const &q2)
  {
    return quantity<U>(static_cast<double>(q1) - static_cast<double>(q2));
  }

  namespace unit_literals
  {
    constexpr quantity<unit::kilogram> operator "" _kg(long double const amount)
    {
      return quantity<unit::kilogram> {static_cast<double>(amount)};
    }

    constexpr quantity<unit::kilogram> operator "" _kg(unsigned long long const amount)
    {
      return quantity<unit::kilogram> {static_cast<double>(amount)};
    }

    constexpr quantity<unit::liter> operator "" _l(long double const amount)
    {
      return quantity<unit::liter> {static_cast<double>(amount)};
    }

    constexpr quantity<unit::meter> operator "" _m(long double const amount)
    {
      return quantity<unit::meter> {static_cast<double>(amount)};
    }

    constexpr quantity<unit::piece> operator "" _pcs(unsigned long long const amount)
    {
      return quantity<unit::piece> {static_cast<double>(amount)};
    }
  }
}

void example_units()
{
  using namespace units;
  using namespace unit_literals;

  auto q1{ 1_kg };
  auto q2{ 4.5_kg };
  auto q3{ q1 + q2 };
  auto q4{ q2 - q1 };

  //auto q5{ 1.0_m + 1_pcs }; // error, cannot add meters and pieces
  //auto q6{ 1_l };   // error, cannot have an integer number of liters
  //auto q7{ 2.0_pcs } // error, can only have an integer number of pieces
}

#include <complex>
#include <chrono>

void Ch02_DemoCreatingCookedUserDefinedLiterals()
{
  FUNC_INFO;
  {
    auto b{ true };    // boolean
    auto s{ "text" };  // const char[7]
    auto i{ 42 };      // int
    auto d{ 42.5 };    // double
    auto p{ nullptr }; // nullptr_t

                       // with prefixes
    auto t1{ L"text" };           // const wchar_t[5]
    auto t2{ LR"(has ' and ")" }; // const wchar_t[5]
    auto hx{ 0xBAD };             // int (in hexadecimal representation)

                                  // with suffixes
    auto a{ 42u };     // unsigned int
    auto l{ 42l };     // signed long
    auto f{ 42.5f };   // float
  }

  {
    using namespace std::string_literals;
    auto s1{ "text"s };  // std::string
    auto s2{ L"text"s }; // std::wstring
    auto s3{ u"text"s }; // std::u16string
    auto s4{ U"text"s }; // std::u32string
  }

  {
    using namespace std::literals::chrono_literals;
    auto timer{ 2h + 42min + 15s }; // std::chrono::duration<long long>
  }

  {
    using namespace std::literals::complex_literals;
    auto c{ 12.0 + 4.5i }; // std::complex<double>
  }

  examples_kb();

  example_units();
}

/*-------------------- Demo Creating Raw User Defined Literals --------------------*/
namespace binary
{
  using byte8 = unsigned char;
  using byte16 = unsigned short;
  using byte32 = unsigned int;

  namespace binary_literals
  {
    namespace binary_literals_internals
    {
      template <typename CharT, char... bits>
      struct binary_struct;

      template <typename CharT, char... bits>
      struct binary_struct<CharT, '0', bits...>
      {
        static constexpr CharT value{
          binary_struct<CharT, bits...>::value };
      };

      template <typename CharT, char... bits>
      struct binary_struct<CharT, '1', bits...>
      {
        static constexpr CharT value{
          static_cast<CharT>(1 << sizeof...(bits)) |
          binary_struct<CharT, bits...>::value };
      };

      template <typename CharT>
      struct binary_struct<CharT>
      {
        static constexpr CharT value{ 0 };
      };
    }

    template<char... bits>
    constexpr byte8 operator""_b8()
    {
      static_assert(
        sizeof...(bits) <= 8,
        "binary literal b8 must be up to 8 digits long");

      return binary_literals_internals::binary_struct<byte8, bits...>::value;
    }

    template<char... bits>
    constexpr byte16 operator""_b16()
    {
      static_assert(
        sizeof...(bits) <= 16,
        "binary literal b16 must be up to 16 digits long");

      return binary_literals_internals::binary_struct<byte16, bits...>::value;
    }

    template<char... bits>
    constexpr byte32 operator""_b32()
    {
      static_assert(
        sizeof...(bits) <= 32,
        "binary literal b32 must be up to 32 digits long");

      return binary_literals_internals::binary_struct<byte32, bits...>::value;
    }

  }
}

void Ch02_DemoCreatingRawUserDefinedLiterals()
{
  FUNC_INFO;
  using namespace binary;
  using namespace binary_literals;

  using namespace binary;
  using namespace binary_literals;

  auto b1 = 1010_b8;
  auto b2 = 101010101010_b16;
  auto b3 = 010101010101010101010101_b32;

  // binary literal b8 must be up to 8 digits long
  //auto b4 = 0011111111_b8;

  // binary literal b16 must be up to 16 digits long
  //auto b5 = 001111111111111111_b16;

  // binary literal b32 must be up to 32 digits long
  //auto b6 = 0011111111111111111111111111111111_b32;
}

/*-------------- test string library helpers --------------*/
namespace string_library
{
  template <typename CharT>
  using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  template <typename CharT>
  using tstringstream = std::basic_stringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  namespace mutable_version
  {
    template<typename CharT>
    inline void to_upper(tstring<CharT>& text)
    {
      std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
    }

    template<typename CharT>
    inline void to_lower(tstring<CharT>& text)
    {
      std::transform(std::begin(text), std::end(text), std::begin(text), tolower);
    }

    template<typename CharT>
    inline void reverse(tstring<CharT>& text)
    {
      std::reverse(std::begin(text), std::end(text));
    }

    template<typename CharT>
    inline void trim(tstring<CharT> & text)
    {
      auto first{ text.find_first_not_of(' ') };
      auto last{ text.find_last_not_of(' ') };
      text = text.substr(first, (last - first + 1));
    }

    template<typename CharT>
    inline void trimleft(tstring<CharT> & text)
    {
      auto first{ text.find_first_not_of(' ') };
      text = text.substr(first, text.size() - first);
    }

    template<typename CharT>
    inline void trimright(tstring<CharT> & text)
    {
      auto last{ text.find_last_not_of(' ') };
      text = text.substr(0, last + 1);
    }
  }

  // ----------

  template<typename CharT>
  inline tstring<CharT> to_upper(tstring<CharT> text)
  {
    std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
    return text;
  }

  template<typename CharT>
  inline tstring<CharT> to_lower(tstring<CharT> text)
  {
    std::transform(std::begin(text), std::end(text), std::begin(text), tolower);
    return text;
  }

  template<typename CharT>
  inline tstring<CharT> reverse(tstring<CharT> text)
  {
    std::reverse(std::begin(text), std::end(text));
    return text;
  }

  template<typename CharT>
  inline tstring<CharT> trim(tstring<CharT> const & text)
  {
    auto first{ text.find_first_not_of(' ') };
    auto last{ text.find_last_not_of(' ') };
    return text.substr(first, (last - first + 1));
  }

  template<typename CharT>
  inline tstring<CharT> trimleft(tstring<CharT> const & text)
  {
    auto first{ text.find_first_not_of(' ') };
    return text.substr(first, text.size() - first);
  }

  template<typename CharT>
  inline tstring<CharT> trimright(tstring<CharT> const & text)
  {
    auto last{ text.find_last_not_of(' ') };
    return text.substr(0, last + 1);
  }

  template<typename CharT>
  inline tstring<CharT> trim(tstring<CharT> const & text, tstring<CharT> const & chars)
  {
    auto first{ text.find_first_not_of(chars) };
    auto last{ text.find_last_not_of(chars) };
    return text.substr(first, (last - first + 1));
  }

  template<typename CharT>
  inline tstring<CharT> trimleft(tstring<CharT> const & text, tstring<CharT> const & chars)
  {
    auto first{ text.find_first_not_of(chars) };
    return text.substr(first, text.size() - first);
  }

  template<typename CharT>
  inline tstring<CharT> trimright(tstring<CharT> const & text, tstring<CharT> const & chars)
  {
    auto last{ text.find_last_not_of(chars) };
    return text.substr(0, last + 1);
  }

  template<typename CharT>
  inline tstring<CharT> remove(tstring<CharT> text, CharT const ch)
  {
    auto start = std::remove_if(std::begin(text), std::end(text), [=](CharT const c) {return c == ch; });
    text.erase(start, std::end(text));
    return text;
  }

  template<typename CharT>
  inline std::vector<tstring<CharT>> split(tstring<CharT> text, CharT const delimiter)
  {
    auto sstr = tstringstream<CharT>{ text };
    auto tokens = std::vector<tstring<CharT>>{};
    auto token = tstring<CharT>{};
    while (std::getline(sstr, token, delimiter))
    {
      if (!token.empty()) tokens.push_back(token);
    }

    return tokens;
  }
}

void Ch02_DemoCreatingStringLibraryHelpers()
{
  FUNC_INFO;
  using namespace std::string_literals;

  auto ut{ string_library::to_upper("this is not UPPERCASE"s) };
  // ut = "THIS IS NOT UPPERCASE"

  auto lt{ string_library::to_lower("THIS IS NOT lowercase"s) };
  // lt = "this is not lowercase"

  auto rt{ string_library::reverse("cookbook"s) }; // rt = "koobkooc"

  auto text1{ "   this is an example   "s };
  auto t1{ string_library::trim(text1) };      // t1 = "this is an example"
  auto t2{ string_library::trimleft(text1) };  // t2 = "this is an example   "
  auto t3{ string_library::trimright(text1) }; // t3 = "   this is an example"

  auto chars1{ " !%\n\r"s };
  auto text3{ "!!  this % needs a lot\rof trimming  !\n"s };
  auto t7{ string_library::trim(text3, chars1) };
  // t7 = "this % needs a lot\rof trimming"

  auto t8{ string_library::trimleft(text3, chars1) };
  // t8 = "this % needs a lot\rof trimming  !\n"

  auto t9{ string_library::trimright(text3, chars1) };
  // t9 = "!!  this % needs a lot\rof trimming"

  auto text4{ "must remove all * from text**"s };
  auto t10{ string_library::remove(text4, '*') };
  // t10 = "must remove all  from text"

  auto t11{ string_library::remove(text4, '!') };
  // t11 = "must remove all * from text**"

  auto text5{ "this text will be split   "s };
  auto tokens1{ string_library::split(text5, ' ') };
  // tokens1 = {"this", "text", "will", "be", "split"}

  auto tokens2{ string_library::split(""s, ' ') };
  // tokens2 = {}
}

/*------------------------ demo string regular expressions ------------------------*/
#include <regex>

template <typename CharT>
using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

template <typename CharT>
bool is_valid_format(tstring<CharT> const & pattern, tstring<CharT> const & text)
{
  auto rx = std::basic_regex<CharT>{ pattern, std::regex_constants::icase };
  return std::regex_match(text, rx);
}

bool is_valid_email_format(std::string const & email)
{
  auto rx = std::regex{ R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s, std::regex_constants::icase };
  return std::regex_match(email, rx);
}

bool is_valid_email_format_w(std::wstring const & text)
{
  return is_valid_format(LR"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s, text);
}

std::tuple<bool, std::string, std::string, std::string> is_valid_email_format_with_result(std::string const & email)
{
  auto rx = std::regex{ R"(^([A-Z0-9._%+-]+)@([A-Z0-9.-]+)\.([A-Z]{2,})$)"s, std::regex_constants::icase };
  auto result = std::smatch{};
  auto success = std::regex_match(email, result, rx);

  return std::make_tuple(
    success,
    success ? result[1].str() : ""s,
    success ? result[2].str() : ""s,
    success ? result[3].str() : ""s);
}

void Ch02_DemoStringUsingRegularExpressions()
{
  FUNC_INFO;
  auto ltest = [](std::string const & email)
  {
    std::cout << std::setw(30) << std::left
      << email << " : "
      << (is_valid_email_format(email) ? "valid" : "invalid")
      << std::endl;
  };

  auto ltest2 = [](auto const & email)
  {
    std::wcout << std::setw(30) << std::left
      << email << L" : "
      << (is_valid_email_format_w(email) ? L"valid" : L"invalid")
      << std::endl;
  };

  auto ltest3 = [](std::string const & email)
  {
    auto valid{ false };
    auto localpart = std::string{};
    auto hostname = std::string{};
    auto dnslabel = std::string{};

    std::tie(valid, localpart, hostname, dnslabel) =
      is_valid_email_format_with_result(email);

    std::cout << std::setw(30) << std::left
      << email << " : "
      << std::setw(10) << (valid ? "valid" : "invalid")
      << std::endl << "   local=" << localpart << ";domain=" << hostname << ";dns=" << dnslabel
      << std::endl;
  };

  ltest("JOHN.DOE@DOMAIN.COM"s);
  ltest("JOHNDOE@DOMAIL.CO.UK"s);
  ltest("JOHNDOE@DOMAIL.INFO"s);
  ltest("J.O.H.N_D.O.E@DOMAIN.INFO"s);
  ltest("ROOT@LOCALHOST"s);
  ltest("john.doe@domain.com"s);

  ltest2(L"JOHN.DOE@DOMAIN.COM"s);
  ltest2(L"JOHNDOE@DOMAIL.CO.UK"s);
  ltest2(L"JOHNDOE@DOMAIL.INFO"s);
  ltest2(L"J.O.H.N_D.O.E@DOMAIN.INFO"s);
  ltest2(L"ROOT@LOCALHOST"s);
  ltest2(L"john.doe@domain.com"s);

  ltest3("JOHN.DOE@DOMAIN.COM"s);
  ltest3("JOHNDOE@DOMAIL.CO.UK"s);
  ltest3("JOHNDOE@DOMAIL.INFO"s);
  ltest3("J.O.H.N_D.O.E@DOMAIN.INFO"s);
  ltest3("ROOT@LOCALHOST"s);
  ltest3("john.doe@domain.com"s);
}

void Ch02_DemoParsingStringContentUsingRegularExpressions()
{
  FUNC_INFO;
  auto text{
    R"(
#remove # to uncomment the following lines
timeout=120
server = 127.0.0.1

#retrycount=3
)"s
  };

  auto rx = std::regex{ R"(^(?!#)(\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*)$)"s };

  {
    auto match = std::smatch{};
    if (std::regex_search(text, match, rx))
    {
      std::cout << match[1] << '=' << match[2] << std::endl;
    }
  }

  {
    auto end = std::sregex_iterator{};
    for (auto it = std::sregex_iterator{ std::begin(text), std::end(text), rx };
      it != end;
      ++it)
    {
      std::cout << '\'' << (*it)[1] << "\'=\'" << (*it)[2] << '\''
        << std::endl;
    }
  }

  {
    auto end = std::sregex_token_iterator{};
    for (auto it = std::sregex_token_iterator{ std::begin(text), std::end(text), rx };
      it != end;
      ++it)
    {
      std::cout << *it << std::endl;
    }
  }

  {
    auto end = std::sregex_token_iterator{};
    for (auto it = std::sregex_token_iterator{ std::begin(text), std::end(text), rx, 1 };
      it != end;
      ++it)
    {
      std::cout << *it << std::endl;
    }
  }

  {
    auto end = std::sregex_token_iterator{};
    for (auto it = std::sregex_token_iterator{ std::begin(text), std::end(text), rx, -1 };
      it != end;
      ++it)
    {
      std::cout << *it << std::endl;
    }
  }
}

void Ch02_DemoReplacingStringContentUsingRegularExpressions()
{
  FUNC_INFO;
  {
    PASS_INFO(1);
    auto text{ "abc aa bca ca bbbb"s };
    auto rx = std::regex{ R"(\b[a|b|c]{3}\b)"s };
    auto newtext = std::regex_replace(text, rx, "---"s);

    std::cout << text << std::endl;
    std::cout << newtext << std::endl;
  }

  {
    PASS_INFO(2);
    auto text{ "abc aa bca ca bbbb"s };
    auto rx = std::regex{ R"(\b[a|b|c]{3}\b)"s };
    auto newtext = std::regex_replace(text, rx, "---"s, std::regex_constants::format_first_only);

    std::cout << text << std::endl;
    std::cout << newtext << std::endl;
  }

  {
    PASS_INFO(3);
    auto text{ "bancila, marius"s };
    auto rx = std::regex{ R"((\w+),\s*(\w+))"s };
    auto newtext = std::regex_replace(text, rx, "$2 $1"s);

    std::cout << text << std::endl;
    std::cout << newtext << std::endl;
  }

  {
    PASS_INFO(4);
    auto text{ "this is a example with a error"s };
    auto rx = std::regex{ R"(\ba ((a|e|i|u|o)\w+))"s };
    auto newtext = std::regex_replace(text, rx, "an $1");

    std::cout << text << std::endl;
    std::cout << newtext << std::endl;
  }

  {
    PASS_INFO(5);
    auto text{ "today is 1.06.2016!!"s };
    auto rx = std::regex{ R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))"s };
    auto newtext1 = std::regex_replace(text, rx, R"($5$4$3$2$1)");
    auto newtext2 = std::regex_replace(text, rx, R"([$`][$&][$'])");

    std::cout << text << std::endl;
    std::cout << newtext1 << std::endl;
    std::cout << newtext2 << std::endl;
  }
}

#include "string_view.h"
std::string get_filename(std::string const & str)
{
  auto const pos1{ str.find_last_of('\\') };
  auto const pos2{ str.find_last_of('.') };
  return str.substr(pos1 + 1, pos2 - pos1 - 1);
}

std::experimental::string_view get_filename_view(std::experimental::string_view str)
{
  auto const pos1{ str.find_last_of('\\') };
  auto const pos2{ str.find_last_of('.') };
  return str.substr(pos1 + 1, pos2 - pos1 - 1);
}

std::experimental::string_view trim_view(std::experimental::string_view str)
{
  auto const pos1{ str.find_first_not_of(" ") };
  auto const pos2{ str.find_last_not_of(" ") };
  str.remove_suffix(str.length() - pos2 - 1);
  str.remove_prefix(pos1);

  return str;
}

void Ch02_DemoUsingStringViewInsteadConstantStringReferences()
{
  FUNC_INFO;
  {
    PASS_INFO(1);
    auto name1 = get_filename(R"(c:\test\example1.doc)"); // example1
    auto name2 = get_filename(R"(c:\test\example2)");     // example2
    if (get_filename(R"(c:\test\_sample_.tmp)").front() == '_')
    {
      std::cout << "underscore" << std::endl;
    }
  }

  {
    PASS_INFO(2);
    char const file1[]{ R"(c:\test\example1.doc)" };
    auto name1 = get_filename_view(file1);
    auto sname1 = name1.to_string();

    std::string file2{ R"(c:\test\example2)" };
    auto name2 = get_filename_view(file2);
    auto sname2 = name2.to_string();

    auto name3 = get_filename_view(std::experimental::string_view(file1, 16));
    auto sname3 = name3.to_string();
  }

  {
    PASS_INFO(3);
    auto sv1{ trim_view("sample") };
    auto sv2{ trim_view("  sample") };
    auto sv3{ trim_view("sample  ") };
    auto sv4{ trim_view("  sample  ") };

    auto s1{ sv1.to_string() };
    auto s2{ sv2.to_string() };
    auto s3{ sv3.to_string() };
    auto s4{ sv4.to_string() };
  }
}
