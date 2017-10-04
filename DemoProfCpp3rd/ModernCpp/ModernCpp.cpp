#include "StdAfx.h"

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>
#include <algorithm>

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
void ModernCppDemoAlias()
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

void ModernCppDemoInitializerList()
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
void ModernCppDemoNonStaticMemberInitialization()
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
void ModernCppDemoAlignment()
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


void ModernCppDemoScopedEnumerations()
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

void ModernCppDemoOverride_Final_For_Virtual_Methods()
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

void ModernCppDemoRangeBasedForLoop()
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
void ModernCppDemoEnableRangeBasedForLoop4CustomTypes()
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


void ModernCppDemoCheckModules()
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

void ModernCppDemoExplicitConstructorAndConversionOperator()
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

