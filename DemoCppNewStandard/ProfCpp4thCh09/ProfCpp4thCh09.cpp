#include "stdafx.h"
#include "ProfCpp4thCh09.h"
#include "SpreadsheetCell09.h"

#include <iostream>
using namespace std;

namespace chap09
{
  void ch09DemoOperatorOverloading()
  {
    FUNC_INFO;
    chap09::SpreadsheetCell myCell(4), anotherCell(5);
    chap09::SpreadsheetCell aThirdCell = myCell + anotherCell;

    // The following two lines don't work with an explicit string ctor
    // string str = "hello";
    // aThirdCell = myCell + str;

    aThirdCell = myCell + 5.6;
    aThirdCell = myCell + 4;

    aThirdCell = 4 + myCell;   // works fine
    aThirdCell = 5.6 + myCell; // works fine
    aThirdCell = 4.5 + 5.5;

    aThirdCell = myCell - anotherCell;
    aThirdCell = myCell * anotherCell;
    aThirdCell = myCell / anotherCell;

    try {
      aThirdCell = myCell / 0;
    }
    catch (const invalid_argument& e) {
      cout << "Caught: " << e.what() << endl;
    }

    aThirdCell -= myCell;
    aThirdCell += 5.4;
    aThirdCell *= myCell;
    aThirdCell /= myCell;

    if (myCell > aThirdCell || myCell < 10) {
      cout << myCell.getValue() << endl;
    }

    if (anotherCell == myCell) {
      cout << "cells are equal\n";
    }
    else {
      cout << "cells are not equal\n";
    }

  }
}
