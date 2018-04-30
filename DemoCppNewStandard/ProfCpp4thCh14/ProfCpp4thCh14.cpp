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
      cout << "myTerminate - Uncaught exception! exiting -1" << endl;
      exit(-1);
    }

    void MyFuncNoException() noexcept
    {
      throw 5;
    }
    void MyFuncTerminator() noexcept
    {
      cout << "caught throw exception error of noexcept function, exiting -2" << endl;
      exit(-2);
    }
  }
  void chap14DemoSetTerminateHandler()
  {
    FUNC_INFO;
    set_terminate(DemoException::myTerminate);
    DemoException::SafeDivide(2, 0);
  }

  void chap14DemoNoexception()
  {
    // A function marked with noexcept should not throw any exceptions
    // When a function marked as noexcept throws an exception anyway, C++ calls terminate() to
    // terminate the application
    FUNC_INFO;
    set_terminate(DemoException::MyFuncTerminator);
    DemoException::MyFuncNoException();
  }

  /*
  Older versions of C++ allowed you to specify the exceptions a function or method intended to
  throw. This specification was called the throw list or the exception specification.

  C++11 has deprecated, and C++17 has removed support for, exception specifications, 
  except for noexcept and throw() which is equivalent to noexcept.

  If a function threw an exception that was not in its exception specification (or throw list), 
  the C++ runtime called std::unexpected() which by default called std::terminate() to terminate
  the application.
  */
  namespace DemoException {
    void readFileThrowExceps(string_view fileName) throw (invalid_argument, runtime_error)
    {
      ifstream inputStream(fileName.data());
      if (inputStream.fail()) {
        // We failed to open the file: throw an exception
        throw runtime_error("Unable to open the file.");
      }
    }
  }

  // demo exception specification
  void chap14DemoThrowList()
  {
    FUNC_INFO;
    try
    {
      DemoException::readFileThrowExceps("unknownfile.txt");
    }
    catch (const runtime_error& e)
    {
      cerr << e.what() << endl;
    }
  }
}