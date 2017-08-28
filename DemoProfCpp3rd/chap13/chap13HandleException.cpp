#include "StdAfx.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include "chap13HandleException.h"

using namespace std;

void readIntegerFile(const string& fileName, vector<int>& dest)
{
  ifstream istr;
  int temp;

  istr.open(fileName.c_str());
  if (istr.fail()) {
    // We failed to open the file: throw an exception
    throw exception();
  }

  // Read the integers one-by-one and add them to the vector
  while (istr >> temp) {
    dest.push_back(temp);
  }
}

void chap13TestThrowException()
{
  vector<int> myInts;
  const string fileName = "IntegerFile.txt";

  try {
    readIntegerFile(fileName, myInts);
  }
  catch (const exception& e)
  {
    cerr << e.what() << " Unable to open file " << fileName << endl;
  }

  for (const auto element : myInts) {
    cout << element << " ";
  }
  cout << endl;
}

// throw mutiple exceptions
void readIntegerFile2(const string& fileName, vector<int>& dest)
{
  ifstream istr;
  int temp;

  istr.open(fileName.c_str());
  if (istr.fail()) {
    // We failed to open the file: throw an exception
    throw runtime_error("Unable to open the file.");
  }

  // Read the integers one-by-one and add them to the vector
  while (istr >> temp) {
    dest.push_back(temp);
  }

  if (!istr.eof()) {
    // We did not reach the end-of-file.
    // This means that some error occurred while reading the file.
    // Throw an exception.
    throw runtime_error("Error reading the file.");
  }
}

void chap13TestMultipleExceptions()
{
  vector<int> myInts;
  const string fileName = "IntegerFile.txt";

  try {
    readIntegerFile2(fileName, myInts);
  }
  catch (const exception& e)
  {
    cerr << e.what() << endl;
  }

  for (const auto element : myInts) {
    cout << element << " ";
  }
  cout << endl;
}

void readIntegerFileTwoTypesExceptions(const string& fileName, vector<int>& dest)
{
  ifstream istr;
  int temp;

  istr.open(fileName.c_str());
  if (istr.fail()) {
    // We failed to open the file: throw an exception
    throw invalid_argument("invalid_argument: Unable to open the file.");
  }

  // Read the integers one-by-one and add them to the vector
  while (istr >> temp) {
    dest.push_back(temp);
  }

  if (!istr.eof()) {
    // We did not reach the end-of-file.
    // This means that some error occurred while reading the file.
    // Throw an exception.
    throw runtime_error("runtime_error: Error reading the file.");
  }
}

void chap13TestMultipleExceptionsTwoTypes()
{
  vector<int> myInts;
  const string fileName = "IntegerFile.txt";

  try {
    readIntegerFileTwoTypesExceptions(fileName, myInts);
  }
  catch (const invalid_argument& e) {
    cerr << e.what() << endl;
  }
  catch (const runtime_error& e) {
    cerr << e.what() << endl;
  }
  // matching any kind of exception
  catch (...)
  {
    cerr << "Error in processing or opening file " << fileName << endl;
  }

  for (const auto element : myInts) {
    cout << element << " ";
  }
  cout << endl;
}

void myTerminate()
{
  cout << "Uncaught exception!" << endl;
  exit(1);
}

/***********************************************************************
* When the program encounters an uncaught exception, it calls the 
* built-in terminate() function, which calls abort() from <cstdlib> 
* to kill the program.
************************************************************************/
void chap13TestUncaughtExceptions()
{
  cout << __func__ << endl;
  vector<int> myInts;
  const string fileName = "IntegerFile.txt";

  // You can set your own terminate_handler by calling set_terminate()
  set_terminate(myTerminate);

  readIntegerFile(fileName, myInts);

  for (const auto element : myInts) {
    cout << element << " ";
  }
  cout << endl;
}

/*
* A function without a throw list can throw exceptions of any type. A
* function with noexcept shouldn�t throw any exception.
*/
void FunctionThrowAnyTypeException()
{
  throw invalid_argument("Function Throw Any Type Exception");
}

// how to specify a function not to throw any excpetion?
// __declspec(nothrow), throw(), noexcept(true), or noexcept
void FunctionNoException() noexcept // C++11 STD
{
  // throw invalid_argument("FunctionNoException noexcept");
}

void FunctionNoException2() throw() // pre-C++11 STD
{
  // throw invalid_argument("FunctionNoException throw()");
}

/***********************************************************************
* throw list or the exception specification are are deprecated in C++11.
* [1] When a function marked as noexcept throws an exception, C++ calls 
*     terminate() to terminate the application.
* [2] When a function throws an exception that is not listed in its throw list, 
*     C++ calls a special function unexpected(). The built-in implementation 
*     of unexpected() calls terminate().
************************************************************************/
void chap13TestThrowList()
{
  cout << __func__ << endl;
  terminate_handler old_handler = set_terminate(myTerminate);

  FunctionThrowAnyTypeException();
  FunctionNoException();
  FunctionNoException2();

  // reset terminate handler when it is done
  set_terminate(old_handler);
}

void testfunc_unlistedExcpetion() throw(runtime_error)
{
  throw 5;
}

// convert an unexpected exception to a runtime_error exception
void myUnexpected()
{
  cerr << "Unexpected exception!" << endl;
  throw runtime_error("");
}


/************************************************************************************
* All versions of Microsoft Visual C++, up to version 2013 at the time of this 
* writing, do not support throw lists for functions as explained earlier. As a
* result, the preceding main() function will catch the int exception because Visual
* C++ just ignores the throw(invalid_argument, runtime_error) specification
* and will issue a warning like �warning C4290: C++ exception specification
* ignored except to indicate a function is not __declspec(nothrow)�. This
* is fine because C++11 has deprecated throw lists.
************************************************************************************/
void chap13TestUnspecifiedExceptions()
{
  cout << __func__ << endl;

  unexpected_handler old_handler = set_unexpected(myUnexpected);

  try {
    testfunc_unlistedExcpetion();
  }
  catch (int e)
  {
    cerr << "Caught int " << e << endl;
  }

  // reset the handler when it is done
  set_unexpected(old_handler);
}

