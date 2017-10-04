#include "StdAfx.h"

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

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


void ModernCppDemoAuto()
{
  printf("-------------------- Function %s --------------------\n", __func__);
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
void ModernCppDemoAlias()
{
  printf("-------------------- Function %s --------------------\n", __func__);
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

void ModernCppDemoInitializerList()
{
  printf("-------------------- Function %s --------------------\n", __func__);
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
void ModernCppDemoNonStaticMemberInitialization()
{
  printf("-------------------- Function %s --------------------\n", __func__);
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
