#include "stdafx.h"
#include "ProfCpp4thCh07.h"

#include <iostream>
using namespace std;
namespace chap07
{
  namespace DemoArray {
    class Simple
    {
    public:
      Simple() { cout << "Simple constructor called!" << endl; }
      ~Simple() { cout << "~Simple destructor called!" << endl; }
    };
  }

  void ch07DemoArrayDeleteOnHeap()
  {
    FUNC_INFO;
    DemoArray::Simple* mySimpleArray = new DemoArray::Simple[4];
    // Use mySimpleArray...
    delete[] mySimpleArray;
    mySimpleArray = nullptr;

    // allocate an array of objects
    const size_t size = 4;
    DemoArray::Simple** mySimplePtrArray = new DemoArray::Simple*[size];

    // Allocate an object for each pointer.
    for (size_t i = 0; i < size; i++)
    { 
      mySimplePtrArray[i] = new DemoArray::Simple;
    }

    // Use mySimplePtrArray ...

    // Delete each allocated object.
    for (size_t i = 0; i < size; i++)
    {
      delete mySimplePtrArray[i];
    }

    // Delete the array itself.
    delete[] mySimplePtrArray;
    mySimplePtrArray = nullptr;
  }

  namespace MultiDimension
  {
    char** allocateCharacterBoard(size_t xDimension, size_t yDimension)
    {
      char** myArray = new char*[xDimension]; // Allocate first dimension

      for (size_t i = 0; i < xDimension; i++)
      {
        myArray[i] = new char[yDimension];  // Allocate ith subarray
      }

      return myArray;
    }

    void releaseCharacterBoard(char** myArray, size_t xDimension)
    {
      for (size_t i = 0; i < xDimension; i++)
      {
        delete[] myArray[i];    //  Delete ith subarray
      }

      delete[] myArray;         //  Delete first dimension
    }

    void doubleInts(int* theArray, size_t size)
    {
      for (size_t i = 0; i < size; i++) {
        theArray[i] *= 2;
        cout << theArray[i] << " ";
      }
      cout << endl;
    }

    template<size_t N>
    void doubleIntsStack(int(&theArray)[N])
    {
      for (size_t i = 0; i < N; i++) {
        theArray[i] *= 2;
        cout << theArray[i] << " ";
      }
      cout << endl;
    }

  }
  void ch07DemoMultiDimensionArray()
  {
    FUNC_INFO;
    char board[3][3] = {};
    // Test code
    board[0][0] = 'X';   // X puts marker in position (0,0).
    board[2][1] = 'O';   // O puts marker in position (2,1).
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        cout << "'" << board[i][j] << "',";
      }
      cout << endl;
    }

    const size_t xDimension = 7;
    const size_t yDimension = 13;
    char** pboard = MultiDimension::allocateCharacterBoard(xDimension, yDimension);
    MultiDimension::releaseCharacterBoard(pboard, xDimension);
  }

  void ch07DemoArrayAndPointer()
  {
    FUNC_INFO;
    size_t arrSize = 4;
    int* heapArray = new int[arrSize] { 1, 5, 3, 4 };
    MultiDimension::doubleInts(heapArray, arrSize);
    //doubleIntsStack(heapArray);	// Does not work.
    delete[] heapArray;
    heapArray = nullptr;

    int stackArray[] = { 5, 7, 9, 11 };
    arrSize = std::size(stackArray);	// Since C++17, requires <array>
                                      //arrSize = sizeof(stackArray) / sizeof(stackArray[0]); // Pre-C++17, see Ch1
    MultiDimension::doubleInts(stackArray, arrSize);
    MultiDimension::doubleInts(&stackArray[0], arrSize);

    MultiDimension::doubleIntsStack(stackArray);
  }
}
