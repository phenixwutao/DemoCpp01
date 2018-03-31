#include "StdAfx.h"
#include "Singleton.h"

namespace SingletonPattern {
  SingletonEarth* SingletonEarth::instance = 0;

  SingletonEarth::SingletonEarth()
  {}

  SingletonEarth* SingletonEarth::Instance() {
    if (instance == 0) {
      instance = new SingletonEarth;    // You can use environment variable to subclassing the intance
    }
    return instance;
  }

  void SingletonEarth::Show() {
    cout << "I'm the only one earth!" << endl
      << "Please protect me!" << endl;
  }

  void TestSingletonPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    auto earth = SingletonEarth::Instance();
    earth->Show();
    delete earth;
  }
}