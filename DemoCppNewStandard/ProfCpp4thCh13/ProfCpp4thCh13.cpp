#include "stdafx.h"
#include "ProfCpp4thCh13.h"

#include <iostream>
#include <locale>
#include <iomanip>
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

  void chap13DemoManipulator()
  {
    FUNC_INFO;
    // Boolean values
    bool myBool = true;
    cout << "This is the default: " << myBool << endl;
    cout << "This should be true: " << boolalpha << myBool << endl;
    cout << "This should be 1: " << noboolalpha << myBool << endl;

    // Simulate "%6d" with streams
    int i = 123;
    printf("This should be '   123': %6d\n", i);
    cout << "This should be '   123': " << setw(6) << i << endl;

    // Simulate "%06d" with streams
    printf("This should be '000123': %06d\n", i);
    cout << "This should be '000123': " << setfill('0') << setw(6) << i << endl;

    // Fill with *
    cout << "This should be '***123': " << setfill('*') << setw(6) << i << endl;
    // Reset fill character
    cout << setfill(' ');

    // Floating point values
    double dbl = 1.452;
    double dbl2 = 5;
    cout << "This should be ' 5': " << setw(2) << noshowpoint << dbl2 << endl;
    cout << "This should be @@1.452: " << setw(7) << setfill('@') << dbl << endl;
    // Reset fill character
    cout << setfill(' ');

    // Instructs cout to start formatting numbers according to your location.
    // Chapter 19 explains the details of the imbue call and the locale object.
    cout.imbue(locale(""));

    // Format numbers according to your location
    cout << "This is 1234567 formatted according to your location: " << 1234567 << endl;

    // Monetary value. What exactly a monetary value means depends on your
    // location. For example, in the USA, a monetary value of 120000 means 120000
    // dollar cents, which is 1200.00 dollars.
    cout << "This should be a monetary value of 120000, "
      << "formatted according to your location: "
      << put_money("120000") << endl;

    // Date and time
#if !defined(_MSC_VER)
    time_t t_t = time(nullptr);  // Get current system time
    tm* t = localtime(&t_t);     // Convert to local time
    cout << "This should be the current date and time formatted according to your location: "
      << put_time(t, "%c") << endl;
#else
    // Visual C++:
    time_t t_t = time(nullptr);
    tm t;
    localtime_s(&t, &t_t);
    cout << "This should be the current date and time formatted according to your location: "
      << put_time(&t, "%c") << endl;
#endif

    // Quoted string
    cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": "
      << quoted("Quoted string with \"embedded quotes\".") << endl;

    // Use setprecision manipulator.
    cout << "This should be '1.2346': " << setprecision(5) << 1.23456789 << endl;

    // Use precision() method
    cout.precision(5);
    cout << "This should be '1.2346': " << 1.23456789 << endl;
  }
}