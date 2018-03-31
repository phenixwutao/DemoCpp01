#pragma once
#include <iostream>
using namespace std;
namespace SingletonPattern {

  class SingletonEarth {
  public:
    static SingletonEarth* Instance();
    void Show();
  protected:
    SingletonEarth();
    SingletonEarth(const SingletonEarth&) = delete;
    SingletonEarth& operator=(const SingletonEarth&) = delete;
  private:
    static SingletonEarth* instance;
  };
  void TestSingletonPattern();
}