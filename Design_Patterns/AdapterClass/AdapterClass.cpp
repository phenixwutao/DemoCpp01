#include "StdAfx.h"
#include "AdapterClass.h"

#include <iostream>
#include <sstream>
using namespace std;

namespace AdapterClass {

  OldVersion::OldVersion()
  {
  }

  void OldVersion::OldDisplay(int input)
  {
    stringstream out;
    out << input;
    cout << out.str() << endl;
  }

  NewVersion::NewVersion(int input)
  {
    myData = input;
  }

  void NewVersion::Display()
  {
  }

  Adapter::Adapter(int input) : NewVersion(input), OldVersion()
  {
  }

  void Adapter::Display()
  {
    OldDisplay(myData);
  }

  void TestAdapterClass()
  {
    printf("in %s\n", __func__);
    int test = 5;
    NewVersion* myInterface;
    myInterface = new Adapter(test);
    myInterface->Display();
    delete myInterface;
  }
}