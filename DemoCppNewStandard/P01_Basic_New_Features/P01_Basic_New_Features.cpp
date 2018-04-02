#include "stdafx.h"
#include "P01_Basic_New_Features.h"
#include <iostream>
#include <vector>
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
  }
  void DemoNullptr()
  {
    FUNC_INFO;
    CheckPointer(nullptr);
    CheckPointer(0);
    CheckPointer(NULL);
  }
}