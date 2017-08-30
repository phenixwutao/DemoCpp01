#include "stdafx.h"

#include <iostream>

#include "SpreadsheetCell.h"
#include "chap14OperatorOverloading.h"
#include "Array.h"
#include "AssociativeArray.h"
#include "Pointer.h"

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

class FunctionObject
{
public:
  int operator() (int inParam);	// Function call operator
  void operator() (string& /*str*/) {}
  int doSquare(int inParam);		// Normal method
};

// Implementation of overloaded function call operator
int FunctionObject::operator() (int inParam)
{
  return doSquare(inParam);
}

// Implementation of normal method
int FunctionObject::doSquare(int inParam)
{
  return inParam * inParam;
}

void chap14TestFunctors()
{
  int x = 3, xSquared, xSquaredAgain;
  FunctionObject square;

  xSquared = square(x);				// Call the function call operator
  xSquaredAgain = square.doSquare(x);	// Call the normal method
}

void chap14TestPointerOperators()
{
  Pointer<int> ap(new int);
  *ap = 5;
  cout << *ap << endl;

  Pointer<SpreadsheetCell> smartCell(new SpreadsheetCell);

  smartCell->set(5); // Dereference and member select the set method.
  cout << smartCell->getValue() << endl;
}

void chap14TestConversionOperators()
{
  SpreadsheetCell cell(1.23);
  string str = cell; // Works as expected
  cout << str << endl;
  double d1 = static_cast<double>(cell);
  cout << d1 << endl;

  double d2 = static_cast<double>(cell) + 3.3; // DOES NOT COMPILE IF YOU DEFINE operator double()
  cout << d2 << endl;

  Pointer<SpreadsheetCell> anotherSmartCell(new SpreadsheetCell(5.0));
  if (anotherSmartCell != nullptr) { cout << "not nullptr" << endl; }
  if (anotherSmartCell != NULL) { cout << "not NULL" << endl; }
  if (anotherSmartCell) { cout << "not nullptr" << endl; }
  if (!anotherSmartCell) { cout << "nullptr" << endl; }
}
