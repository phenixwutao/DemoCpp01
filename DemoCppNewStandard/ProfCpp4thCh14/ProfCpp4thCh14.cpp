#include "stdafx.h"
#include "ProfCpp4thCh14.h"

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <fstream>
#include <exception>

using namespace std;
namespace chap14
{
  namespace DemoException
  {
    double SafeDivide(double num, double den)
    {
      if (den == 0)
        throw invalid_argument("Divide by zero");
      return num / den;
    }

    vector<int> readInputFile(string_view fileName)
    {
      ifstream inputStream(fileName.data());
      if (inputStream.fail()) {
        // We failed to open the file: throw an exception
        throw exception();
      }

      // Read the integers one-by-one and add them to a vector
      vector<int> integers;
      int temp;
      while (inputStream >> temp) {
        integers.push_back(temp);
      }
      return integers;
    }

    void ThrowIntFile(string_view input)
    {
      ifstream inputStream(input.data());
      if (inputStream.fail()) {
        // We failed to open the file: throw an exception
        throw 5;
      }
    }

    void ThrowCharFile(string_view fileName)
    {
      ifstream inputStream(fileName.data());
      if (inputStream.fail()) {
        // We failed to open the file: throw an exception
        throw "Unable to open file";
      }
    }

    void ThrowMultipleExceptionFile(string_view fileName)
    {
      ifstream inputStream(fileName.data());
      if (inputStream.fail()) {
        // We failed to open the file: throw an exception
        throw runtime_error("Unable to open the file.");
      }
    }
  }

  void chap14DemoSafeDivide()
  {
    FUNC_INFO;
    try {
      cout << DemoException::SafeDivide(5, 2) << endl;
      cout << DemoException::SafeDivide(10, 0) << endl;
      cout << DemoException::SafeDivide(3, 3) << endl;
    }
    catch (const invalid_argument& e) {
      cout << "Caught exception: " << e.what() << endl;
    }
  }

  void chap14DemoFileException()
  {
    FUNC_INFO;
    const string fileName = "IntegerFile.txt";
    vector<int> myInts;

    try {
      myInts = DemoException::readInputFile(fileName);
    }
    catch (const exception& /* e */) {
      cerr << "Unable to open file " << fileName << endl;
      return;
    }
  }

  void chap14DemoThrowInt()
  {
    FUNC_INFO;
    const string fileName = "IntegerFile.txt";
    try {
      DemoException::ThrowIntFile(fileName);
    }
    catch (int e) {
      cerr << "Unable to open file " << fileName << " (" << e << ")" << endl;
      return;
    }
  }

  void chap14DemoThrowChars()
  {
    FUNC_INFO;
    const string fileName = "IntegerFile.txt";

    try {
      DemoException::ThrowCharFile(fileName);
    }
    catch (const char* e) {
      cerr << e << endl;
    }
  }

  void chap14DemoCatchMultipleException()
  {
    FUNC_INFO;
    const string fileName = "IntegerFile.txt";

    try {
      DemoException::ThrowMultipleExceptionFile(fileName);
    }
    catch (const exception& e) {
      cerr << e.what() << endl;
    }
  }

  void chap14DemoThrowMoreTypes()
  {
    FUNC_INFO;
    try {
      DemoException::SafeDivide(10,0);
      DemoException::ThrowMultipleExceptionFile("MyInputTest.text");
    }
    catch (const invalid_argument& e)
    {
      cerr << e.what() << endl;
    }
    catch (const runtime_error& e)
    {
      cerr << e.what() << endl;
    }
  }

  void chap14DemoCatchAnyException()
  {
    FUNC_INFO;
    try {
      DemoException::SafeDivide(10, 0);
    }
    catch (...)
    {
      cerr << "Error in function" << endl;
    }
  }

  namespace DemoException
  {
    void myTerminate()
    {
      cout << "myTerminate - Uncaught exception!" << endl;
      exit(1);
    }
  }
  void chap14DemoSetTerminateHandler()
  {
    FUNC_INFO;
    set_terminate(DemoException::myTerminate);
    DemoException::SafeDivide(2, 0);
  }
}
