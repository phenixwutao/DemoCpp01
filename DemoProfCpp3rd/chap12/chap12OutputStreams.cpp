#include "StdAfx.h"

#include <iostream>
#include <sstream>
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
      // put back last read character
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
  // cin getline method
  constexpr const size_t kBufferSize = 256;
  char buffer[kBufferSize];
  cin.getline(buffer, kBufferSize);
  cout << "read1:'" << buffer << "'" << endl;

  // string std::getline method
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

  // Read all three values. Note that chips is represented
  // by the strings "true" and "false"
  inStream >> description >> size >> boolalpha >> hasChips;
  muffin.setSize(size);
  muffin.setDescription(description);
  muffin.setHasChocolateChips(hasChips);

  return muffin;
}

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
