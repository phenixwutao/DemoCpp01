#pragma once
#include <iostream>
using namespace std;
namespace ProxyPattern {

  class Gun {
  public:
    Gun(const char* name);
    ~Gun();
    void ShowMe();
    void Load(int num);
    void Shoot();

  private:
    const char* gName;
    int bullet;
  };


  // Virtual Proxy  // Only when the gun is shooting, return the real gun
  class GunProxy {
  public:
    GunProxy(const char* name);
    ~GunProxy();
    void ShowMe();
    void Load(int num);
    void Shoot();

  private:
    Gun* gun = nullptr;
    const char* gName;
    int bullet;
  };
  void TestProxyPattern();
}