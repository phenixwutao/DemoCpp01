#include "stdafx.h"
#include "P04_New_Library_Features.h"

#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

namespace NewLibraryFeatures {
  void DemoStaticAssert()
  {
    FUNC_INFO;
    const int val = 9;
    static_assert((1 <= val && val <=10),
      "val is out of range");

    static_assert(CHAR_BIT == 8, // ordinary
      "chars don't have 8 bits \u2620"); // string
    static_assert(CHAR_BIT == 8,
      L"chars don't have 8 bits \u2620"); // wide string
    static_assert(CHAR_BIT == 8,
      u8"chars don't have 8 bits \u2620"); // UTF-8
    static_assert(CHAR_BIT == 8,
      u"chars don't have 8 bits \u2620"); // UTF-16
    static_assert(CHAR_BIT == 8,
      U"chars don't have 8 bits \u2620"); // UTF-32
  }

  namespace DemoConversion
  {
    class Widget
    {
    public:
      explicit Widget(int i)
      {
      }
      explicit Widget(string name)
      {
      }
      ~Widget() {}

      //implicit conversion
      //operator int() const
      //{ return 3; }

      // explicit conversion
      explicit operator int() const
      { return 3; }

      explicit operator std::string() const
      {
        return "demo";
      }

      explicit operator bool() const
      {
        return false;
      }
    };
    void func(int a)
    {
      printf("a = %d\n", a);
    }
  }
  void DemoConversionOperator()
  {
    FUNC_INFO;
    DemoConversion::Widget wid(1);
    DemoConversion::func(static_cast<int>(wid));
    cout << static_cast<std::string>(wid) << endl;
  }

  namespace ClassDeclType
  {
    struct S { double d {3.1}; };

    template<typename T>
    auto myfunc(T x, T y) -> decltype(x + y)
    {
      return x + y; 
    }

    template<typename T1, typename T2>
    auto mult(T1&& a, T2&& b) ->
      decltype(std::forward<T1>(a) * std::forward<T2>(b))
    {
      return std::forward<T1>(a) * std::forward<T2>(b);
    }
  }
  void DemoDeclType()
  {
    FUNC_INFO;
    int x, *ptr;
    decltype(x) i1; // i1’s type is int
    decltype(ptr) p1; // p1’s type is int*
    std::size_t sz = sizeof(decltype(ptr[44])); // sz = sizeof(int);
                                                // ptr[44] not evaluated

    // quirks for class decltype:
    const ClassDeclType::S* p;
    // double
    decltype(p->d) x1;

    //const double&
    const double kPI = 3.14;
    decltype((p->d)) x2(kPI);

    auto wResult = ClassDeclType::myfunc(1, 2);
    cout << "wResult = " << wResult << endl;
    auto dResult = ClassDeclType::myfunc(1.1, 2.2);
    cout << "dResult = " << dResult << endl;

    auto wOut = ClassDeclType::mult(2, 3);
    cout << "wOut = " << wOut << endl;
    auto dOut = ClassDeclType::mult(1.1, 1.3);
    cout << "dOut = " << dOut << endl;

    string a("hi,");
    string b("Adam");
    auto sOut = ClassDeclType::myfunc(a,b);
    cout << "sOut = " << sOut << endl;

  }
}