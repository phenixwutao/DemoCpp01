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
    // namespace alias
    namespace MyMath = MyLib::MyMath::General;

    cout << "MyMath::add " << MyMath::add(1, 2) << endl;
  }

}
