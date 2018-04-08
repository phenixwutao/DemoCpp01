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

}