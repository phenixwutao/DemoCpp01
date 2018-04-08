#include "stdafx.h"
#include "ProfCpp4thCh01.h"

#include <iostream>
#include <string>
using namespace std;
namespace chap01
{
  void ch01Typetest()
  {
    FUNC_INFO;
    int someInteger = 256;
    short someShort;
    long someLong;
    float someFloat;
    double someDouble;

    someInteger++;
    someInteger *= 2;
    someShort = static_cast<short>(someInteger);
    someLong = someShort * 10000;
    someFloat = someLong + 0.785f;
    someDouble = static_cast<double>(someFloat) / 100000;
    cout << someDouble << endl;

    auto a1 = 0x3.ABCp-10;
    auto a2 = 0Xb.cp12l;
    cout << "a1 = " << a1 << " a2 = " << a2 << endl;
  }

  int MyLib::MyMath::General::add(int a, int b)
  {
    return a + b;
  }

  void ch01DemoNamespaceCpp17()
  {
    FUNC_INFO;
    // namespace alias
    namespace MyMath = MyLib::MyMath::General;

    cout << "MyMath::add " << MyMath::add(1, 2) << endl;
  }

  // By default, the underlying enumeration value is an integer,
  // but this can be changed as follows:
  enum class PieceType : unsigned long
  {
    King = 1,
    Queen,
    Rook = 10,
    Pawn
  };

  void ch01DemoEnumClass()
  {
    FUNC_INFO;
    PieceType piece = PieceType::King;
    int val = static_cast<int>(piece);
    if (piece == PieceType::King)
    {
      printf("it is king\n");
    }

    if (val == 1)
    {
      printf("it is king\n");
    }
    else
      printf("it is not king\n");

  }

  void ch01DemoSwitchFallthrough()
  {
    FUNC_INFO;
    // With C++17, you can tell the compiler that a fallthrough is intentional
    // using the [[fallthrough]] attribute as follows:
    int iCol = 2;
    switch (iCol)
    {
    case 1:
      [[fallthrough]]; // tell the compiler that a fallthrough is intentional
    case 2:
      printf("group 1\n");
      break;
    case 3:
      [[fallthrough]]; // tell the compiler that a fallthrough is intentional
    case 4:
      printf("group 2\n");
      break;
    default:
      printf("group default\n");
      break;
    }

    auto func2 = [=](int i)->int {return i + 2; };
    switch (int i = 1;  func2(i))
    {
    case 1:
      printf("case 1 i = %d\n", i);
    case 3:
      printf("case 3 i = %d\n", i);
    case 5:
      printf("case 5 i = %d\n", i);
      break;

    default:
      printf("unhandled number %d\n", i);
      break;
    }
  }

  namespace FunctionReturnType
  {
    auto calc(int a, int b) ->decltype (a+b)
    {
      return a + b;
    }
    auto calc2(int a, int b)
    {
      return a + b;
    }
    template<typename T1, typename T2>
    auto calc3(T1&& a, T2&& b)
    {
      return a + b;
    }
    template<typename T1, typename T2> // detect return type is optional
    auto calc4(const T1& a, const T2& b) -> decltype(a+b)
    {
      return a + b;
    }
  }
  void ch01DemoFunctionReturnTypeDeduction()
  {
    FUNC_INFO;
    printf("calc %d\n", FunctionReturnType::calc(1,2));
    printf("calc2 %d\n", FunctionReturnType::calc2(1, 2));

    cout << "calc3 " << FunctionReturnType::calc3(1.1, 1.2) << endl;
    cout << "calc3 " << FunctionReturnType::calc3(3, 4) << endl;
    string a1("hi,");
    string a2("Adam");
    cout << "calc3 " << FunctionReturnType::calc3(a1, a2) << endl;

    cout << "calc4 " << FunctionReturnType::calc4(1.1, 1.2) << endl;
    cout << "calc4 " << FunctionReturnType::calc4(3, 4) << endl;
    cout << "calc4 " << FunctionReturnType::calc4(a1, a2) << endl;
  }
}
