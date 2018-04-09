#include "stdafx.h"
#include "ProfCpp4thCh02.h"

#include <iostream>
#include <string>
#include <string_view>
#include <cstddef>
using namespace std;
namespace chap02
{
  namespace OldCCtring
  {
    char* copyString(const char* str)
    {
      printf("in %s\n", __func__);
      const auto wSize = strlen(str)+1;
      //char* result = new char[wSize];  // BUG! Off by one!
      char* result = new char[wSize];
      strcpy_s(result, wSize, str);
      return result;
    }

    char* appendStrings(const char* str1, const char* str2, const char* str3)
    {
      printf("in %s\n", __func__);
      char result[15];
      auto wError = strcpy_s(result, str1);
      cout << "wError " << wError << ", result " << result << endl;

      wError = strcat_s(result, str2);
      cout << "wError " << wError << ", result " << result << endl;

      wError = strcat_s(result, str3);
      cout << "wError " << wError << ", result " << result << endl;

      const auto wSize = strlen(str1) + strlen(str2) + strlen(str3) + 1;
      char* cBuffer = new char[wSize];
      strcpy_s(cBuffer, wSize, result);
      return cBuffer;
    }
  }

  void ch02DemoCString()
  {
    const char* str1 = "Hello";
    char* copy = OldCCtring::copyString(str1);
    cout << copy << endl;
    delete[] copy;
    copy = nullptr;

    const char* str2 = " World";
    const char* str3 = "!";
    char* result = OldCCtring::appendStrings(str1, str2, str3);
    cout << result << endl;
    delete[] result;
    result = nullptr;
  }

  void ch02DemoStringLengthSize()
  {
    FUNC_INFO;
    char text1[] = "abcdef";
    size_t s1 = sizeof(text1);  // is 7
    size_t s2 = strlen(text1);  // is 6
    cout << "text sizeof " << s1 << endl << "text len " << s2 << endl;

    const char* text2 = "abcdef";
    size_t s3 = sizeof(text2);  // size of pointer is platform-dependent (e.g. 4 bytes for x86, 8 bytes for x64)
    size_t s4 = strlen(text2);  // is 6
    cout << "text sizeof " << s3 << endl << "text len " << s4 << endl;

  }

  void ch02DemoRawStringAndConst()
  {
    FUNC_INFO;
    //const char* str1 = "Hello "World"!";    // Error!
    const char* str2 = "Hello \"World\"!";
    const char* str3 = R"(Hello "World"!)";

    const char* str4 = "Line 1\nLine 2";
    const char* str5 = R"(Line 1
Line 2)";

    const char* str6 = R"(Is the following a tab character? \t)";
    cout << str4 << endl;
    cout << str5 << endl;
    cout << str6 << endl;

    //const char* str7 = R"(Embedded )" characters)";    // Error!
    const char* str8 = R"-(Embedded )" characters)-";
    const char* str9 = R"MYPP(Embedded )" characters)MYPP";
    cout << str8 << endl;
    cout << str9 << endl;
  }

  void ch02DemoStringCmpConversion()
  {
    FUNC_INFO;
    const char* name1 = "Martin";
    const char* name2 = "Martina";
    auto wOut = strcmp(name1, name2);
    if (wOut < 0)
      printf("name1 %s is less than name2 %s\n", name1, name2);
    else if (wOut > 0)
      printf("name1 %s is greater than name2 %s\n", name1, name2);
    else
      printf("name1 %s the same as name2 %s\n", name1, name2);


    const string toParse = "   123USD";
    size_t index = 0;
    int value = stoi(toParse, &index);
    cout << "Parsed value: " << value << endl;
    cout << "First non-parsed character: '" << toParse[index] << "'" << endl;
  }

  namespace StringView {
    // C++17 std::string_view class
    string_view extractExtension(string_view fileName)
    {
      return fileName.substr(fileName.rfind('.'));
    }
  }

  /*
  * Use an std::string_view instead of const std::string& or const char* 
  * whenever a function or method requires a read-only string as one of 
  * its parameters.
  */
  void ch02DemoStringViews()
  {
    FUNC_INFO;
    // C++ std::string.
    string fileName = R"(c:\temp\my file.ext)";
    cout << "C++ string: " << StringView::extractExtension(fileName) << endl;

    // C-style string.
    const char* cString = R"(c:\temp\my file.ext)";
    cout << "C string: " << StringView::extractExtension(cString) << endl;

    // String literal.
    cout << "Literal: " << StringView::extractExtension(R"(c:\temp\my file.ext)") << endl;

    // Raw string buffer with given length.
    const char* raw = "test.ext";
    size_t length = strlen(raw);
    cout << "Raw: " << StringView::extractExtension(string_view(raw, length)) << endl;

    // Assigning the result to a std::string.
    string extension = StringView::extractExtension(fileName).data();

    string str = "Hello";
    string_view sv = " world";
    auto result = str + sv.data();
    cout << result << endl;

    // user-defined literal "sv" stands for string_view object
    auto sVW1 = "My string_view"sv;
  }

}
