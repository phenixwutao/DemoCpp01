#include "stdafx.h"
#include "ProfCpp4thCh14.h"

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <sstream>

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

    /*
    Older versions of C++ allowed you to specify the exceptions a function or method intended to
    throw. This specification was called the throw list or the exception specification.

    C++11 has deprecated, and C++17 has removed support for, exception specifications,
    except for noexcept and throw() which is equivalent to noexcept.

    If a function threw an exception that was not in its exception specification (or throw list),
    the C++ runtime called std::unexpected() which by default called std::terminate() to terminate
    the application.
    */
    void readFileThrowExceps(string_view fileName) throw (invalid_argument, runtime_error)
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
      DemoException::SafeDivide(10, 0);
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


  namespace MyExcepClass
  {

    class FileError : public exception
    {
    public:
      FileError(string_view fileName) : mFileName(fileName) {}
      virtual const char* what() const noexcept override { return mMessage.c_str(); }
      string_view getFileName() const noexcept { return mFileName; }

    protected:
      void setMessage(string_view message) { mMessage = message; }

    private:
      string mFileName;
      string mMessage;
    };

    class FileOpenError : public FileError
    {
    public:
      FileOpenError(string_view fileName)
        : FileError(fileName)
      {
        setMessage("Unable to open "s + fileName.data());
      }
    };

    class FileReadError : public FileError
    {
    public:
      FileReadError(string_view fileName, size_t lineNumber)
        : FileError(fileName), mLineNumber(lineNumber)
      {
        ostringstream ostr;
        ostr << "Error reading " << fileName << " at line " << lineNumber;
        setMessage(ostr.str());
      }

      size_t getLineNumber() const noexcept { return mLineNumber; }

    private:
      size_t mLineNumber;
    };


    vector<int> readOwnFile(string_view fileName)
    {
      ifstream inputStream(fileName.data());
      if (inputStream.fail()) {
        // We failed to open the file: throw an exception
        throw FileOpenError(fileName);
      }

      vector<int> integers;
      size_t lineNumber = 0;
      while (!inputStream.eof()) {
        // Read one line from the file
        string line;
        getline(inputStream, line);
        ++lineNumber;

        // Create a string stream out of the line
        istringstream lineStream(line);

        // Read the integers one-by-one and add them to a vector
        int temp;
        while (lineStream >> temp) {
          integers.push_back(temp);
        }

        if (!lineStream.eof()) {
          // We did not reach the end of the string stream.
          // This means that some error occurred while reading this line.
          // Throw an exception.
          throw FileReadError(fileName, lineNumber);
        }
      }

      return integers;
    }
  }

  void chap14DemoCustomiseExceptionClass()
  {
    FUNC_INFO;
    const string fileName = "IntegerFile.txt";

    try {
      auto myInts = MyExcepClass::readOwnFile(fileName);
    }
    catch (const MyExcepClass::FileError& e)
    {
      cerr << e.what() << endl;
      return;
    }
  }

  namespace NestedException
  {
    class MyException : public exception
    {
    public:
      MyException(string_view message) : mMessage(message) {}
      virtual const char* what() const noexcept override { return mMessage.c_str(); }

    private:
      string mMessage;
    };

    void doSomething()
    {
      try {
        throw runtime_error("Throwing a runtime_error exception");
      }
      catch (const runtime_error& /*e*/) {
        cout << __func__ << " caught a runtime_error" << endl;
        cout << __func__ << " throwing MyException" << endl;
        throw_with_nested(MyException("MyException with nested runtime_error"));
      }
    }
  }
  void chap14DemoNestedException()
  {
    FUNC_INFO;
    try {
      NestedException::doSomething();
    }
    catch (const NestedException::MyException& e)
    {
      cout << __func__ << " caught MyException: " << e.what() << endl;
      try {
        rethrow_if_nested(e);
      }
      catch (const runtime_error& e)
      {
        // Handle nested exception
        cout << "  Nested exception: " << e.what() << endl;
      }
    }
  }

  namespace DemoRethrow {
    void g()
    {
      throw invalid_argument("Some exception from g");
    }

    void f()
    {
      try {
        g();
      }
      catch (const invalid_argument& e) {
        cout << "caught in f: " << e.what() << endl;
        throw;  // rethrow
      }
    }
  }
  void chap14DemoRethrowException()
  {
    FUNC_INFO;
    try {
      DemoRethrow::f();
    }
    catch (const invalid_argument& e) {
      cout << "caught in main: " << e.what() << endl;
    }
  }


  namespace DemoSlicing
  {
    void g() { throw invalid_argument("Some exception"); }

    void f()
    {
      try {
        g();
      }
      catch (const exception& e) {
        cout << "caught in f: " << e.what() << endl;
        throw;  // rethrow
        //throw e; // throw slicing
      }
    }
  }
  void chap14DemoThrowSlicing()
  {
    FUNC_INFO;
    try {
      DemoSlicing::f();
    }
    catch (const invalid_argument& e) {
      cout << "invalid_argument caught in main: " << e.what() << endl;
    }
    catch (const exception& e) {
      cout << "exception caught in main: " << e.what() << endl;
    }
  }

  namespace DemoCatchRethrow
  {
    void funcOne();
    void funcTwo();

    void funcOne()
    {
      string str1;
      string* str2 = new string();
      try {
        funcTwo();
      }
      catch (...) {
        delete str2;
        throw; // rethrow the exception
      }
      delete str2;
    }

    void funcTwo()
    {
      ifstream fileStream;
      fileStream.open("filename.txt");
      throw exception();
      fileStream.close();
    }
  }
  void chap14DemoCatchAndRethrow()
  {
    FUNC_INFO;
    try {
      DemoCatchRethrow::funcOne();
    }
    catch (const exception& e) {
      cerr << "Exception caught! " << e.what() << endl;
      return;
    }
  }

  namespace NewHandle
  {
    class please_terminate_me : public bad_alloc { };

    void myNewHandler()
    {
      cerr << "Unable to allocate memory." << endl;
      throw please_terminate_me();
    }
  }
  void chap14DemoSetNewHandler()
  {
    try {
      // Set the new new_handler and save the old one.
      new_handler oldHandler = set_new_handler(NewHandle::myNewHandler);

      // Generate allocation error
      size_t numInts = numeric_limits<size_t>::max();
      int* ptr = new int[numInts];

      // Reset the old new_handler if pass memory allocation without any error
      set_new_handler(oldHandler);
    }
    catch (const NewHandle::please_terminate_me&) {
      cerr << __FILE__ << "(" << __LINE__
        << "): Terminating program." << endl;
      return;
    }
  }

  namespace ExpptionInCtor
  {
    class SubObject
    {
    public:
      SubObject(int i)
      {
        throw runtime_error("Exception by SubObject ctor");
      }
    };

    class MyClass
    {
    public:
      MyClass();
    private:
      int* mData = nullptr;
      SubObject mSubObject;
    };

    MyClass::MyClass()
      try
      : mData(new int[42]{ 1, 2, 3 }), mSubObject(42)
    {
      /* ... constructor body ... */
    }
    catch (const exception& e)
    {
      // Cleanup memory.
      delete[] mData;
      mData = nullptr;
      cout << "function-try-block caught: '" << e.what() << "'" << endl;
    }

  }
  void chap14DemoFunctionTryBlocksForConstructors()
  {
    FUNC_INFO;
    try {
      ExpptionInCtor::MyClass m;
    }
    catch (const exception& e) {
      cout << "my caught: '" << e.what() << "'" << endl;
    }

  }
}

