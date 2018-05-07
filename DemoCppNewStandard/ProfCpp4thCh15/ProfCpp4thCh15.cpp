#include "stdafx.h"
#include "ProfCpp4thCh15.h"
#include "SpreadsheetCell1.h"
#include "MyArray.h"
#include "MemoryDemo.h"

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

  void printArray(const Array<int>& arr)
  {
    for (size_t i = 0; i < arr.getSize(); i++) {
      cout << arr[i] << " "; // calls the const operator[] because arr is a const object.
    }
    cout << endl;
  }

  void chap15DemoSubscriptOperator()
  {
    FUNC_INFO;
    Array<int> myArray;
    for (size_t i = 0; i < 10; i++) {
      myArray[i] = 100;	// Calls the non-const operator[] because myArray is a non-const object.
    }
    printArray(myArray);

    //Array<int> myArray;
    //for (size_t i = 0; i < 10; i++) {
    //	myArray.setElementAt(i, 100);
    //}
    //for (size_t i = 0; i < 10; i++) {
    //	cout << myArray.getElementAt(i) << " ";
    //}

  }


  class FunctionObject
  {
  public:
    int operator() (int param);	// Function call operator
    void operator() (string_view /*str*/) {}
    int doSquare(int param);		// Normal method
  };

  // Implementation of overloaded function call operator
  int FunctionObject::operator() (int param)
  {
    return doSquare(param);
  }

  // Implementation of normal method
  int FunctionObject::doSquare(int param)
  {
    return param * param;
  }

  void chap15DemoFunctor()
  {
    FUNC_INFO;
    int x = 3, xSquared, xSquaredAgain;
    FunctionObject square;

    xSquared = square(x);				// Call the function call operator
    xSquaredAgain = square.doSquare(x);	// Call the normal method
  }

  void chap15DemoConversionOperator()
  {
    FUNC_INFO;
    Tut1::SpreadsheetCell cell(1.23);
    double d1 = static_cast<double>(cell); // need static_cast
    cout << "SpreadsheetCell in double presentation: " << d1 << endl;
    string str = cell;
    cout << "SpreadsheetCell in string presentation: " << str << endl;

  }

  void chap15DemoExplicitConversionOperator()
  {
    FUNC_INFO;
    // Explicit operator double() demonstration
    Tut1::SpreadsheetCell cell2 = 6.6;
    string str = cell2;
    double d3 = static_cast<double>(cell2);
    double d4 = static_cast<double>(cell2 + 3.3);
    cout << str << endl;
    cout << d3 << endl;
    cout << d4 << endl;
  }

  void chap15DemoOverloadNewDelete()
  {
    Tut2::MemoryDemo* mem = new Tut2::MemoryDemo();
    delete mem;

    mem = new Tut2::MemoryDemo[10];
    delete[] mem;

    mem = new (nothrow) Tut2::MemoryDemo();
    delete mem;

    mem = new (nothrow) Tut2::MemoryDemo[10];
    delete[] mem;

    Tut2::MemoryDemo* memp = new(5) Tut2::MemoryDemo();
    delete memp;
  }
}