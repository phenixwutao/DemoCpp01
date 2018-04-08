#include "stdafx.h"
#include "ProfCpp4thCh01.h"

#include <iostream>
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

}
