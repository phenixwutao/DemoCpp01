#include "StdAfx.h"

#include <iostream>
#include <cstring>
#include "chap12OutputStreams.h"

using namespace std;

// raw output an array of char
void rawWrite(const char* data, size_t dataSize)
{
  cout.write(data, dataSize);
}

// raw output a char
void rawPutChar(const char* data, size_t charIndex)
{
  cout.put(data[charIndex]);
}

void chap12TestStreams()
{
  const char* test = "hello there\n";
  auto wSize = strlen(test);
  rawWrite(test, wSize);

  for (size_t i = 0; i < wSize; i++)
  {
    rawPutChar(test, i);
  }

  cout << "cout abc";
  cout.flush();    // abc is written to the console.
  cout << "def";
  cout << endl;    // def is written to the console.

  cerr << "cerr abc";   // abc is written to console, cerr doesn't buffer
  cerr << "def";
  cerr << endl;

  // exception handling
  cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
  try
  {
    cout << "Hello World." << endl;
  }
  catch (const ios_base::failure& ex)
  {
    cerr << "Caught exception: " << ex.what()
      << ", error code = " << ex.code() << endl;
  }

}