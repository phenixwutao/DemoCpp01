#include "StdAfx.h"
#include "Proxy.h"
namespace ProxyPattern {
  // Class Gun
  Gun::Gun(const char *name) : gName(name), bullet(0)
  {}

  Gun::~Gun()
  {}

  void Gun::ShowMe()
  {
    cout << "Type   :  " << gName << endl;
    cout << "Bullet :  " << bullet << endl;
  }

  void Gun::Load(int num) {
    bullet += num;
  }

  void Gun::Shoot()
  {
    cout << gName << " is shooting!" << endl;
    bullet--;
  }

  // Class GunProxy
  GunProxy::GunProxy(const char *name) : gName(name), bullet(0)
  {
  }

  GunProxy::~GunProxy()
  {
    delete gun;
  }

  void GunProxy::ShowMe()
  {
    if (gun != nullptr)
    {
      gun->ShowMe();
    }
    else {
      cout << "Type   :  " << gName << endl;
      cout << "Bullet :  " << bullet << endl;
    }
  }

  void GunProxy::Load(int num) {
    if (gun != nullptr)
    {
      gun->Load(num);
    }
    else {
      bullet += num;
    }
  }

  void GunProxy::Shoot() {
    if (gun == nullptr)
    {
      gun = new Gun(gName);
      gun->Load(bullet);
    }
    gun->Shoot();
  }

  void TestProxyPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    GunProxy myGun("AK47");
    myGun.ShowMe();
    myGun.Load(99);
    myGun.ShowMe();
    myGun.Shoot();
    myGun.ShowMe();
  }
}