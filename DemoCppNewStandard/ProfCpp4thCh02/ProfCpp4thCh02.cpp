#include "stdafx.h"
#include "ProfCpp4thCh02.h"

#include <iostream>
#include <string>
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
}
