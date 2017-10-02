#include "StdAfx.h"

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

#include "ModernCpp.h"

using namespace std;

void ModernCppDemoAuto()
{
  {
    auto i = 42;				              // int
    auto d = 42.5;				            // double
    auto s = "text";				          // const char*
    auto b = new char[10]{ 0 };		    // char*
    auto p = std::make_shared<int>(42);	// std::shared_ptr<int>
    auto v = { 1, 2, 3 };			      // std::initializer_list<int>
    auto l = [](char const c) {return toupper(c); }; // lambda int(char)

    if (b != nullptr)
      delete[] b;
  }

  {
    auto s = std::string{ "text" };		   // std::string
    auto v = std::vector<int>{ 1, 2, 3 };	// std::vector<int>
  }

  {
    auto v = std::vector<int>{ 1, 2, 3 };
    int size1 = v.size();	// implicit conversion, possible loss of data
    auto size2 = v.size();
    //auto size3 = int{ v.size() }; // error, narrowing conversion
  }

  {
    std::map<int, std::string> m;

    for (std::map<int, std::string>::const_iterator it = m.cbegin();
      it != m.cend();
      ++it)
    {
    }

    for (auto it = m.cbegin(); it != m.cend(); ++it)
    {
    }
  }

}
