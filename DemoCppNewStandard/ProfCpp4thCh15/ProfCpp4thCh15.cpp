#include "stdafx.h"
#include "ProfCpp4thCh15.h"
#include "SpreadsheetCell1.h"

#include <iostream>
using namespace std;

namespace chap15
{
  void chap15DemoOverloadOperatorsBasic()
  {
    FUNC_INFO;
    Tut1::SpreadsheetCell c1(4);
    Tut1::SpreadsheetCell c2(6);

    cout << (c1 == c2) << endl;
    cout << (c1 < c2) << endl;
    cout << (c1 != c2) << endl;
    cout << (c1 > c2) << endl;
    cout << (c1 <= c2) << endl;
    cout << (c1 >= c2) << endl;
  }
}