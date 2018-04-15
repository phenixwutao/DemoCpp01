#include "stdafx.h"
#include "ProfCpp4thCh11.h"

#include <iostream>
#include <string>
#include <cstddef>
#include <array>
using namespace std;

namespace chap11
{
  namespace REF
  {
    std::string getString()
    {
      return "Hello world!";
    }
  }

  void chap11DemoUseReference()
  {
    FUNC_INFO;
    int x = 3, y = 4, z = 5;
    int& xRef = x;
    xRef = 10;
    //  int& emptyRef; // DOES NOT COMPILE!

    //  int& unnamedRef1 = 5;   // DOES NOT COMPILE
    const int& unnamedRef2 = 5; // Works as expected

    // std::string& string1 = getString();   // DOES NOT COMPILE
    const std::string& string2 = REF::getString(); // Works as expected

    xRef = y; // changes value of x to 4. Doesn't make xRef refer to y.

    int& zRef = z;
    zRef = xRef; // Assigns values, not references

    int* intP;
    int*& ptrRef = intP;
    ptrRef = new int;
    *ptrRef = 5;
    delete ptrRef;

    int* xPtr = &xRef; // address of a reference is pointer to value
    *xPtr = 100;
  }


  namespace UsePtr
  {
    void printIntArr(const int arr[], size_t size)
    {
      for (size_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
      }
      cout << endl;
    }

    void separateOddsAndEvens(const int arr[], size_t size,
                              int** odds, size_t* numOdds, 
                              int** evens, size_t* numEvens)
    {
      // Count the number of odds and evens
      *numOdds = *numEvens = 0;
      for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 1)
        {
          ++(*numOdds);
        }
        else
        {
          ++(*numEvens);
        }
      }

      // Allocate two new arrays of the appropriate size.
      *odds = new int[*numOdds];
      *evens = new int[*numEvens];

      // Copy the odds and evens to the new arrays
      size_t oddsPos = 0, evensPos = 0;
      for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 1)
        {
          (*odds)[oddsPos++] = arr[i];
        }
        else
        {
          (*evens)[evensPos++] = arr[i];
        }
      }
    }
  }
  void chap11DemoUsePointer()
  {
    FUNC_INFO;
    int unSplit[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* oddNums = nullptr;
    int* evenNums = nullptr;
    size_t numOdds = 0, numEvens = 0;

    UsePtr::separateOddsAndEvens(unSplit, std::size(unSplit), &oddNums, &numOdds, &evenNums, &numEvens);
    UsePtr::printIntArr(oddNums, numOdds);
    UsePtr::printIntArr(evenNums, numEvens);

    delete[] oddNums; oddNums = nullptr;
    delete[] evenNums; evenNums = nullptr;
  }
}
