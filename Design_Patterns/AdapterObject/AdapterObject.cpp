#include "StdAfx.h"
#include "AdapterObject.h"

#include <iostream>
#include <sstream>
using namespace std;

namespace AdapterObject {

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

  void NewVersion::Display() {
  }

  Adapter::Adapter(int input) : NewVersion(input)
  {
    if (oldVersion == nullptr)
      oldVersion = new OldVersion();
  }

  void Adapter::Display()
  {
    oldVersion->OldDisplay(myData);
  }

  Adapter::~Adapter()
  {
    delete oldVersion;
  }

  void TestAdapterObject()
  {
    printf("in %s\n", __func__);
    NewVersion* myVer = new Adapter(5);
    myVer->Display();
    delete myVer;
  }
}