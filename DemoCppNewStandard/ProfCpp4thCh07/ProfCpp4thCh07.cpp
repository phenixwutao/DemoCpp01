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


}
