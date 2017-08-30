#include "stdafx.h"

#include <iostream>

#include "SpreadsheetCell.h"
#include "chap14OperatorOverloading.h"
#include "Array.h"
#include "AssociativeArray.h"

using namespace std;

void chap14TestArithmeticOperators()
{
  SpreadsheetCell c1(4);
  SpreadsheetCell c2(4);
  SpreadsheetCell c3;

  c1++;
  ++c2;
  c3 = -c1;
}

void chap14TestSubscriptOperators()
{
  Array<int> myarr;
  constexpr const size_t kSize = 10;
  for (size_t i = 0; i < kSize; i++)
    myarr[i] = 10;

  for (size_t i = 0; i < kSize; i++)
    cout << myarr[i] << " ";
  cout << endl;

  AssociativeArray<int> myArray;
  myArray["Key 1"] = 11;
  myArray["Key 2"] = 22;
  myArray["Key 3"] = 33;
  myArray.Print();

  try {
    cout << myArray["Key 1"] << endl;
    cout << myArray["Key 2"] << endl;

    // Test const operator[]
    const AssociativeArray<int>& c = myArray;
    cout << c["Key 3"] << endl;
    cout << c["Key 4"] << endl;
  }
  catch (const invalid_argument& ex) {
    cout << "Caught exception: " << ex.what() << endl;
  }

}
