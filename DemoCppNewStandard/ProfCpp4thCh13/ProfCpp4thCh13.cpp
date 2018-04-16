#include "stdafx.h"
#include "ProfCpp4thCh13.h"

#include <iostream>
#include <stdexcept>
using namespace std;
namespace chap13
{
  /******************************************************************************************
  *cin	An input stream, reads data from the "input console."
  *cout	A buffered output stream, writes data to the "output console."
  *cerr	An unbuffered output stream, writes data to the "error console," which is often the same as the "output console."
  *clog	A buffered version of cerr
  *
  * The difference between buffered and unbuffered streams is that a buffered stream 
  * does not immediately send the data to the destination, but instead, it buffers 
  * incoming data and then sends it in blocks. An unbuffered stream, on the other hand, 
  * immediately sends the data to the destination. Buffering is usually done to 
  * improve performance, as certain destinations, such as files, perform better when 
  * writing bigger blocks at once. Note that you can always force a buffered stream to 
  * send all its currently buffered data to the destination by flushing its buffer 
  * using the flush() method
  *******************************************************************************************/
  void chap13DemoBasicStream()
  {
    int x = 5;
    cerr << "error " << x << endl;
    clog << "log x=" << x << endl;

    const char* test = "hello there\n";
    cout.write(test, strlen(test));
    cout.put('a');
    cout << endl;
    cout << "test flush\n";
    cout.flush(); // explicitly tell the stream to flush its buffer

    if (cout.good()) {
      cout << "All good" << endl;
    }

    if (cout.fail())
    {
      cerr << "Unable to flush to standard out" << endl;
    }
    
    // Streams have a conversion operator to convert to type bool
    if (!cout)
    {
      cerr << "Unable to flush to standard out" << endl;
    }
  }

  void chap13DemoCoutException()
  {
    FUNC_INFO;
    cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
    try {
      cout << "Hello World." << endl;
    }
    catch (const ios_base::failure& ex) {
      cerr << "Caught exception: " << ex.what()
           << ", error code = " << ex.code() << endl;
    }
  }

}