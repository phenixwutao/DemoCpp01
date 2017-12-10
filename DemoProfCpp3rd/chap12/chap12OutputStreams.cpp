#include "StdAfx.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include <ios>
#include <iomanip>

#include "chap12OutputStreams.h"
#include "Muffin.h"

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

void chap12TestManipulators()
{
  // Boolean values
  bool myBool = true;
  cout << "This is the default: " << myBool << endl;
  cout << "This should be true: " << boolalpha << myBool << endl;
  cout << "This should be 1: " << noboolalpha << myBool << endl;

  // Simulate "%6d" with streams
  int i = 123;
  printf("This should be ' 123': %6d\n", i);
  cout << "This should be ' 123': " << setw(6) << i << endl;

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
  // Chapter 18 explains the details of the imbue call and the locale object.
  cout.imbue(locale(""));

  // Format numbers according to your location
  cout << "This is 1234567 formatted according to your location: " << 1234567 <<
    endl;

  // Money amount
  cout << "This should be a money amount of 120000, "
    << "formatted according to your location: "
    << put_money("120000") << endl;

  // Date and time
  time_t t_t = time(nullptr); // Get current system time

  tm tmDummy;
  auto t = localtime_s(&tmDummy, &t_t); // Convert to local time
  cout << "This should be the current date and time "
    << "formatted according to your location: "
    << put_time(&tmDummy, "%c") << endl;

  // C++14: Quoted string
  cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": "
    << quoted("Quoted string with \"embedded quotes\".") << endl;
}

string readName(istream& inStream)
{
  string name;
  char next;
  // The get() method allows raw input of data from a stream
  while (inStream.get(next)) {
    if (next == std::char_traits<char>::eof())
      break;
    else
      name += next;
  }

  return name;
}

void chap12TestInputGet()
{
  cout << "Reading a name from cin. You can usually close cin with Control-D (Control-Z in Windows): ";
  string theName = readName(cin);

  cout << "The name is \"" << theName.c_str() << "\"" << endl;
}

void chap12TestInputUnget()
{
  string guestName;
  int partySize = 0;
  // Read characters until we find a digit
  char ch;
  cin >> noskipws;
  while (cin >> ch)
  {
    if (isdigit(ch))
    {
      // unget put back last read character
      cin.unget();
      if (cin.fail())
        cout << "unget() failed" << endl;
      break;
    }
    guestName += ch;
  }
  // Read partysize
  cin >> partySize;

  cout << "Thank you '" << guestName.c_str()
       << "', party of " << partySize << endl;
  if (partySize > 10)
  {
    cout << "An extra gratuity will apply." << endl;
  }
}


void chap12TestInputPeek()
{
  string guestName;
  int partySize = 0;
  // Read characters until we find a digit
  char ch;
  cin >> noskipws;
  while (true) {
    // 'peek' at next character
    auto wp = cin.peek();
    ch = static_cast<char>(wp);
    if (!cin.good())
      break;
    if (isdigit(ch)) {
      // next character will be a digit, so stop the loop
      break;
    }
    // next character will be a non-digit, so read it
    cin >> ch;
    guestName += ch;
  }
  // Read partysize
  cin >> partySize;

  cout << "Thank you '" << guestName
    << "', party of " << partySize << endl;
  if (partySize > 10) {
    cout << "An extra gratuity will apply." << endl;
  }
}

void chap12TestInputGetline()
{
  // version 1: cin getline method
  constexpr const size_t kBufferSize = 256;
  char buffer[kBufferSize];
  cin.getline(buffer, kBufferSize);
  cout << "read1:'" << buffer << "'" << endl;

  // version 2: string std::getline method
  string myString;
  std::getline(cin, myString);
  cout << "read2:'" << myString << "'" << endl;
}

void chap12TestInputErrorCheck()
{
  cout << "Enter numbers on separate lines to add.\n"
       << "Use Control+D to finish (Control+Z in Windows, then Enter)." << endl;
  int sum = 0;

  if (!cin.good()) {
    cerr << "Standard input is in a bad state!" << endl;
  }

  int number;
  while (!cin.bad())
  {
    cin >> number;
    if (cin.good())
    {
      sum += number;
    }
    else if (cin.eof())
    {
      break; // Reached end of file
    }
    else if (cin.fail())
    {
      // Failure!
      cin.clear(); // Clear the failure state.
      string badToken;
      cin >> badToken; // Consume the bad input.
      cerr << "WARNING: Bad input encountered: " << badToken << endl;
    }
  }

  cout << "The sum is " << sum << endl;
}


Muffin createMuffin(istringstream& inStream)
{
  Muffin muffin;
  // Assume data is properly formatted:
  // Description size chips

  string description;
  int size;
  bool hasChips;

  // Reading or extract data from a string stream:
  // Read all three values. Note that chips is represented
  // by the strings "true" and "false"
  inStream >> description >> size >> boolalpha >> hasChips;
  muffin.setSize(size);
  muffin.setDescription(description);
  muffin.setHasChocolateChips(hasChips);

  return muffin;
}

/*******************************************************************************
* Turning an object into a "flattened" type, like a string, is often called
* marshalling.Marshalling is useful for saving objects to disk or sending them
* across a network. 
*******************************************************************************/
void chap12TestMuffin()
{
  cout << "First, let's create a muffin in code and output it." << endl;

  Muffin m;
  m.setDescription("Giant_Blueberry_Muffin");
  m.setSize(42);
  m.setHasChocolateChips(false);

  m.output();

  cout << "Now we'll create a muffin from a string stream" << endl;

  istringstream instream("My_Muffin 2 true");
  Muffin m2 = createMuffin(instream);

  m2.output();
}

void chap12TestStringStream()
{
  // The ostringstream class is used to write data to a string, 
  // while the istringstream class is used to read data from a string.
  cout << "Enter tokens. Control+D (Unix) or Control+Z (Windows) to end" << endl;
  ostringstream outStream;
  while (cin)
  {
    string nextToken;
    cout << "Next token: ";
    cin >> nextToken;
    if (nextToken == "done")
      break;
    outStream << "'" << nextToken << "',";
  }
  cout << "The end result is: " << outStream.str() << endl;;
}

void chap12TestOutputFileStream(int argc, char** argv)
{
  ofstream outFile("test.txt", ios_base::trunc);
  if (!outFile.good())
  {
    cerr << "Error while opening output file!" << endl;
  }
  outFile << "There were " << argc << " arguments to this program." << endl;
  outFile << "They are: " << endl;
  for (int i = 0; i < argc; i++)
  {
    outFile << i << "):  " << argv[i] << endl;
  }
  outFile.close();
}

// Page 363: Jumping with Seek and Tell
// seek method is used for moving position to a specified place,
// seekp() is used for seek put(write) position of output stream
// seekg() is used for seek get(read) position of input stream
// tellp() is used for telling current position of output stream
// tellg() is used for telling current position of input stream

void chap12TestJumpingWithSeekTell()
{
  ofstream fout("test.out");
  if (!fout)
  {
    cerr << "Error opening test.out for writing" << endl;
  }

  // 1. Output the string "12345".
  fout << "12345";

  // 2. Verify that the marker is at position 5.
  auto curPos = fout.tellp();
  if (5 == curPos)
  {
    cout << "Test passed: Currently at position 5" << endl;
  }
  else
  {
    cout << "Test failed: Not at position 5" << endl;
  }

  // 3. Move to position 2 in the stream.
  fout.seekp(2, ios_base::beg);

  // 4. Output a 0 in position 2 and close the stream.
  fout << 0;
  fout.close();

  // 5. Open an input stream on test.out.
  ifstream fin("test.out");
  if (!fin) {
    cerr << "Error opening test.out for reading" << endl;
  }

  // 6. Read the first token as an integer.
  int testVal;
  fin >> testVal;

  // 7. Confirm that the value is 12045.
  const int expected = 12045;
  if (testVal == expected) {
    cout << "Test passed: Value is " << expected << endl;
  }
  else {
    cout << "Test failed: Value is not " << expected
      << "(it was " << testVal << ")" << endl;
  }
}

void chap12TestLinkStream()
{
  ifstream inFile("input.txt");  // Note: input.txt must exist.
  ofstream outFile("output.txt");

  // Set up a link between inFile and outFile.
  inFile.tie(&outFile);
  // Output some text to outFile. Normally, this would
  // not flush because std::endl is not sent.
  outFile << "Hello there!";

  // outFile has NOT been flushed.
  // Read some text from inFile. This will trigger flush()
  // on outFile.
  string nextToken;
  inFile >> nextToken;
  // outFile HAS been flushed.
  inFile.close();
  outFile.close();
}

void changeNumberForID(const string& inFileName, int inID, const string& inNewNumber)
{
  fstream ioData(inFileName.c_str());
  if (!ioData)
  {
    cerr << "Error while opening file " << inFileName << endl;
    return;
  }

  // Loop until the end of file
  while (ioData.good())
  {
    int id;
    string number;

    // Read the next ID.
    ioData >> id;

    // Check to see if the current record is the one being changed.
    if (id == inID)
    {
      // Seek the write position to the current read position
      ioData.seekp(ioData.tellg());
      // Output a space, then the new number.
      ioData << " " << inNewNumber;
      break;
    }

    // Read the current number to advance the stream.
    ioData >> number;
    cout << "searching:" << inID << " in id: " << id << ", number:" << number << endl;
  }

  if(ioData.is_open() == true)
    ioData.close();
}

void chap12TestBidirectionalIO()
{
  changeNumberForID("data.txt", 263, "415-555-3333");
}