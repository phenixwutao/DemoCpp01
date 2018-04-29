#include "stdafx.h"
#include "ProfCpp4thCh13.h"

#include <iostream>
#include <locale>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <string>
#include <string_view>
#include <fstream>

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


  namespace DemoInput
  {
    void MyInput()
    {
      string userInput;
      cin >> userInput;
      cout << "User input was " << userInput << endl;

      int intInput;
      cin >> intInput;
      cout << "User input was " << intInput << endl;

      string guestName;
      int partySize;
      cout << "Name and number of guests: ";
      cin >> guestName >> partySize;
      cout << "Thank you, " << guestName << "." << endl;
      if (partySize > 10) {
        cout << "An extra gratuity will apply." << endl;
      }
    }

    void MyInputErrors()
    {
      cout << "Enter numbers on separate lines to add. "
        << "Use Control+D to finish (Control+Z in Windows)." << endl;
      int sum = 0;

      if (!cin.good()) {
        cerr << "Standard input is in a bad state!" << endl;
        return;
      }

      int number;
      while (!cin.bad()) {
        cin >> number;
        if (cin.good()) {
          sum += number;
        }
        else if (cin.eof()) {
          break; // Reached end of file
        }
        else if (cin.fail()) {
          // Failure!
          cin.clear(); // Clear the failure state.
          string badToken;
          cin >> badToken; // Consume the bad input.
          cerr << "WARNING: Bad input encountered: " << badToken << endl;
        }
      }

      cout << "The sum is " << sum << endl;
    }


    string readName1(istream& stream)
    {
      string name;
      while (stream) { // Or: while (!stream.fail()) {
        int next = stream.get();//returns the next character in the stream
        if (!stream || next == std::char_traits<char>::eof())
          break;
        name += static_cast<char>(next);// Append character.
      }
      return name;
    }


    string readName2(istream& stream)
    {
      string name;
      char next;
      while (stream.get(next))
      {
        name += next;
      }

      return name;
    }

    /*****************************************************************************************
    * A call to unget() causes the stream to back up by one position, essentially putting the
    * previous character read back on the stream. You can use the fail() method to see if unget()
    * was successful or not. For example, unget() can fail if the current position is at the
    * beginning of the stream.
    *****************************************************************************************/
    void DemoUngetData()
    {
      string guestName;
      int partySize = 0;

      // Read characters until we find a digit
      char ch = '\0';
      cin >> noskipws;
      while (cin >> ch) {
        if (isdigit(ch)) {
          cin.unget();
          if (cin.fail())
            cout << "unget() failed" << endl;
          break;
        }
        guestName += ch;
      }
      // Read partysize, if the stream is not in error state
      if (cin)
        cin >> partySize;
      if (!cin) {
        cerr << "Error getting party size." << endl;
        return;
      }

      cout << "Thank you '" << guestName
        << "', party of " << partySize << endl;
      if (partySize > 10) {
        cout << "An extra gratuity will apply." << endl;
      }
    }

    // putback() takes the character being placed back on the stream as a parameter
    void MyPutback()
    {
      char cFlag;
      cin >> cFlag;
      cin.putback('e');
    }

    // peek() method allows you to preview the next value that would be returned
    // if you were to call get().
    void MyPeek()
    {
      string guestName;
      int partySize = 0;

      // Read characters until we find a digit
      char ch;
      cin >> noskipws;
      while (true) {
        // 'peek' at next character
        ch = static_cast<char>(cin.peek());
        if (!cin)
          break;
        if (isdigit(ch)) {
          // next character will be a digit, so stop the loop
          break;
        }
        // next character will be a non-digit, so read it
        cin >> ch;
        if (!cin)
          break;
        guestName += ch;
      }
      // Read partysize, if the stream is not in error state
      if (cin)
        cin >> partySize;
      if (!cin) {
        cerr << "Error getting party size." << endl;
        return;
      }

      cout << "Thank you '" << guestName
        << "', party of " << partySize << endl;
      if (partySize > 10) {
        cout << "An extra gratuity will apply." << endl;
      }
    }

    void MyGetline()
    {
      const int kBufferSize = 1024;
      char buffer[kBufferSize] = { 0 };
      // The getline() method fills a character buffer with a line of data
      // up to the specified size.
      cin.getline(buffer, kBufferSize);

      cout << "***" << buffer << "***" << endl;

      // std::getline doesn't require you to specify the size of the buffer
      string myString;
      std::getline(cin, myString);
      cout << "***" << myString << "***" << endl;
    }

  } // End of namespace DemoInput


  namespace InOutObject
  {
    class Muffin
    {
    public:
      virtual ~Muffin() = default;

      string_view getDescription() const;
      void setDescription(string_view description);

      int getSize() const;
      void setSize(int size);

      bool hasChocolateChips() const;
      void setHasChocolateChips(bool hasChips);

      void output() const;

    private:
      string mDescription;
      int mSize = 0;
      bool mHasChocolateChips = false;
    };

    string_view Muffin::getDescription() const { return mDescription; }
    void Muffin::setDescription(string_view description) { mDescription = description; }

    int Muffin::getSize() const { return mSize; }
    void Muffin::setSize(int size) { mSize = size; }

    bool Muffin::hasChocolateChips() const { return mHasChocolateChips; }
    void Muffin::setHasChocolateChips(bool hasChips) { mHasChocolateChips = hasChips; }

    void Muffin::output() const
    {
      printf("%s, Size is %d, %s\n", getDescription().data(), getSize(),
        (hasChocolateChips() ? "has chips" : "no chips"));
    }

    Muffin createMuffin(istringstream& stream)
    {
      Muffin muffin;
      // Assume data is properly formatted:
      // Description size chips

      string description;
      int size;
      bool hasChips;

      // Read all three values. Note that chips is represented
      // by the strings "true" and "false"
      stream >> description >> size >> boolalpha >> hasChips;
      if (stream) { // Reading was successful.
        muffin.setSize(size);
        muffin.setDescription(description);
        muffin.setHasChocolateChips(hasChips);
      }

      return muffin;
    }

  }

  void chap13DemoInputOutputWithObjects()
  {
    FUNC_INFO;
    cout << "First, let's create a muffin in code and output it." << endl;

    InOutObject::Muffin myMuffin;
    myMuffin.setDescription("Giant_Blueberry_Muffin");
    myMuffin.setSize(42);
    myMuffin.setHasChocolateChips(false);

    printf("The muffin is ");
    myMuffin.output();
    printf(" -- yummy!\n");


    cout << "Now we'll create a muffin from a string stream" << endl;

    istringstream instream("My_Muffin 2 true");
    InOutObject::Muffin m2 = InOutObject::createMuffin(instream);
    m2.output();
  }


  /*
  An advantage of string streams over standard C++ strings is that, in addition to data, they know
  where the next read or write operation will take place, also called the current position. Another
  advantage is that string streams support manipulators and locales to enable more powerful formatting
  compared to strings.
  */
  void chap13DemoOstringStream()
  {
    FUNC_INFO;
    cout << "Enter tokens. Control+D (Unix) or Control+Z (Windows) to end." << endl;

    ostringstream outStream;

    while (cin) {
      string nextToken;

      cout << "Next token: ";
      cin >> nextToken;

      if (!cin || nextToken == "done")
        break;

      outStream << nextToken << "\t";
    }

    cout << "The end result is: " << outStream.str() << endl;
  }

  void chap13DemoFileStream()
  {
    ofstream outFile("test.txt", ios_base::trunc);
    if (!outFile.good()) {
      cerr << "Error while opening output file!" << endl;
      return;
    }
    string text("where are you");
    outFile << "There were " << text << " arguments to this program." << endl;
    outFile.close();
  }

  void chap13DemoFileStreamSeekTell()
  {
    FUNC_INFO;
    string fileName("test2.out");
    ofstream fout(fileName);
    if (!fout) {
      cerr << "Error opening "<< fileName <<" for writing" << endl;
      return;
    }

    // 1. Output the string "12345".
    fout << "12345";

    // 2. Verify that the marker is at position 5.
    streampos curPos = fout.tellp();
    if (5 == curPos) {
      cout << "Test passed: Currently at position 5" << endl;
    }
    else {
      cout << "Test failed: Not at position 5" << endl;
    }

    // 3. Move to position 2 in the stream.
    fout.seekp(2, ios_base::beg);

    // 4. Output a 0 in position 2 and close the stream.
    fout << 0;
    fout.close();

    // 5. Open an input stream on test.out.
    ifstream fin(fileName);
    if (!fin) {
      cerr << "Error opening " << fileName << " for reading" << endl;
      return;
    }

    // 6. Read the first token as an integer.
    int testVal;
    fin >> testVal;
    if (!fin) {
      cerr << "Error reading from file" << endl;
      return;
    }

    // 7. Confirm that the value is 12045.
    const int expected = 12045;
    if (testVal == expected)
    {
      cout << "Test passed: Value is " << expected << endl;
    }
    else
    {
      cout << "Test failed: Value is not " << expected
        << " (it was " << testVal << ")" << endl;
    }
  }

}
