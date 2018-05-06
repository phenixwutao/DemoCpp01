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

  void chap15DemoOverloadingIncrementAndDecrement()
  {
    FUNC_INFO;
    int i, j = 4;
    i = -j; // unary minus
    i = +i; // unary plus
    j = +(-i); // apply unary plus to the result of applying unary minus to i
    j = -(-i); // apply unary minus to the result of applying unary minus to i

    i = i + 1;
    i += 1;
    ++i;
    i++;

    Tut1::SpreadsheetCell c1(4);
    Tut1::SpreadsheetCell c2(4);
    Tut1::SpreadsheetCell c3 = -c1;
    c1++;
    ++c2;
  }

  void chap15DemoExtractionInsertionOperator()
  {
    FUNC_INFO;
    //int number = 10;
    //cout << "The number is " << number << endl;
    //string str;
    //cin >> number >> str;

    Tut1::SpreadsheetCell myCell, anotherCell, aThirdCell;

    cout << "Input 3 spreadsheetcells:" << endl;
    cin >> myCell >> anotherCell >> aThirdCell;
    cout << myCell << " " << anotherCell << " " << aThirdCell << endl;

    cout << "Input 3 spreadsheetcells:" << endl;
    operator>>(operator>>(operator>>(cin, myCell), anotherCell), aThirdCell);
  }
}