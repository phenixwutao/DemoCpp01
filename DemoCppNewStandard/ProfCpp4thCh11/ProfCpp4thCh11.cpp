#include "stdafx.h"
#include "ProfCpp4thCh11.h"

#include <iostream>
#include <string>
#include <cstddef>
#include <array>
#include <vector>
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

  namespace UsePair
  {
    void printVec(const vector<int>& arr)
    {
      for (const auto& i : arr) {
        cout << i << " ";
      }
      cout << endl;
    }

    pair<vector<int>, vector<int>> separateOddsAndEvens(const vector<int>& arr)
    {
      vector<int> odds, evens;
      for (const auto i : arr)
      {
        if (i % 2 == 1)
        {
          odds.push_back(i);
        }
        else
        {
          evens.push_back(i);
        }
      }
      return make_pair(odds, evens);
    }

  }
  void chap11DemoUsePair()
  {
    FUNC_INFO;
    vector<int> vecUnSplit = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto[odds, evens] = UsePair::separateOddsAndEvens(vecUnSplit);
    UsePair::printVec(odds);
    UsePair::printVec(evens);
  }

  namespace UseConst
  {
    const double PI = 3.141592653589793238462;

    void func(const int /*param*/)
    {
      // Not allowed to change param...
    }

    void constIntOne()
    {
      const int* ip;
      ip = new int[10];
      //  ip[4] = 5; // DOES NOT COMPILE!
      delete[] ip;
    }

    void constIntTwo()
    {
      int const* ip;
      ip = new int[10];
      //  ip[4] = 5; // DOES NOT COMPILE!
      delete[] ip;
    }

    void constPtrOne()
    {
      int* const ip = nullptr;
      //  ip = new int[10]; // DOES NOT COMPILE!
      ip[4] = 5;	// Error: dereferencing a null pointer
    }

    void constPtrTwo()
    {
      // const pointer pointing to non-const int type:
      int* const ip = new int[10];  // cannot change pointer
      ip[4] = 5;                    // can change the value pointing to
      delete[] ip;
    }

    void constIntPtrOne()
    {
      int const* const ip = nullptr;
    }

    void constIntPtrTwo()
    {
      const int* const ip = nullptr;
    }

    void manyLevelConst()
    {
      const int * const * const * const ip = nullptr;
    }

    class BigClass;
    void doSomething(const BigClass& /*arg*/)
    {
      // implementation here
    }
  }
  void chap11DemoUseConst()
  {
    int* ip;
    ip = new int[10];
    ip[4] = 5;
    delete[] ip;

    int z;
    const int& zRef = z;
    //  zRef = 4; // DOES NOT COMPILE

    UseConst::constPtrTwo();
  }
}
