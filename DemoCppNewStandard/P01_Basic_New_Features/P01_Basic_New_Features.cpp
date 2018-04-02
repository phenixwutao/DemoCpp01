#include "stdafx.h"
#include "P01_Basic_New_Features.h"

#include <iostream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

namespace BasicNewFeatures {
  void DemoBasicForLoop()
  {
    FUNC_INFO;
    vector<int> vec;
    for (int i = 1; i <= 10; ++i)
    {
      vec.emplace_back(i);
    }

    for (auto& it : vec)
    {
      cout << it << "\t";
    }
    cout << endl;

    for (volatile auto& it : vec)
    {
      it += 3;
      cout << it << "\t";
    }
    cout << endl;

    DEMO_INFO("ranged based for loop on array");
    short employee[10]{1};
    for (auto& it : employee)
    {
      cout << it << "\t";
    }
    cout << endl;
  }
  namespace {
    void CheckPointer(int* pVal)
    {
      printf("calling %s(int* pVal)\n", __func__);
    }
    void CheckPointer(int Val)
    {
      printf("calling %s(int Val)\n", __func__);
    }
    void CheckNullPointer(int* pVal)
    {
      printf("calling %s(int* pVal)\n", __func__);
    }
  }
  void DemoNullptr()
  {
    FUNC_INFO;
    CheckPointer(nullptr);
    CheckPointer(0);
    CheckPointer(NULL);
  }
  
  template<typename F, typename P>
  void logAndCall(F func, P param)
  {
    func(param);
  }

  void DemoTemplateFunctionNullptr()
  {
    // logAndCall(CheckNullPointer, 0); // error
    // logAndCall(CheckNullPointer, NULL); // error
    logAndCall(CheckNullPointer, nullptr); // ok
  }
  void DemoUnicodeSupport()
  {
    FUNC_INFO;
    std::string   s1("hello");     // std::basic_string<char>
    std::wstring  s2(L"hello");    // std::basic_string<wchar_t>
    std::u16string s3(u"hello");   // std::basic_string<char16_t>
    std::u32string s4(U"hello");   // std::basic_string<char32_t>
  }

  void DemoRawString()
  {
    std::string noNewlines(R"(\n\n)");
    std::string cmd(R"(ls /home/docs | grep ".pdf")");
    std::string withNewlines(R"(Line 1 of the string...
                                Line 2 C:\IT2\8.5\SCM ...
                                Line 3)");
    cout << noNewlines << endl;
    cout << cmd << endl;
    cout << withNewlines << endl;

    auto s1 = LR"(Raw Wide string literal \t (without a tab))";
    auto s2 = u8R"(Raw UTF-8 string literal \n (without a newline))";
    auto s3 = uR"(Raw UTF-16 string literal \\ (with two backslashes))";
    auto s4 = UR"(Raw UTF-32 string literal \u2620 (without a code point))";

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;

    // Raw text delimiters may be customized:
    // R"!(        )!"
    // R"xyzzy(    )xyzzy"
    std::regex re1(R"!("operator\(\)"|"operator->")!"); // "operator()"|
                                                        // "operator->"
    std::regex re2(R"xyzzy("\([A-Za-z_]\w*\)")xyzzy"); // "(identifier)"
    auto name = R"HHH(test folder C:\Program files\IT2 Solutions\AppServer;)HHH";
    cout << name << endl;
  }
}