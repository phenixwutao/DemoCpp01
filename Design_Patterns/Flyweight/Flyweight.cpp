#include "stdAfx.h"
#include "Flyweight.h"
#include <iostream>

namespace FlyweightPattern
{
  // Class Gun
  Gun::~Gun() 
  {}

  Gun::Gun(const char *name) : gName(name), bullet(0)
  {}

  Gun::Gun(const Gun &rhs)
  {
    gName = rhs.gName;
    bullet = rhs.bullet;
  }

  void Gun::Load(int num)
  {
    bullet = num;
  }

  bool Gun::operator == (const Gun &rhs)
  {
    if (strcmp(gName, rhs.gName) != 0)
      return false;
    else if (bullet != rhs.bullet)
      return false;
    else
      return true;
  }

  bool Gun::operator == (const char* rhs)
  {
    if (strcmp(gName, rhs) == 0)
      return true;
    else
      return false;
  }

  void Gun::ShowMe()
  {
    cout << "Name   :  " << gName << endl;
    cout << "Bullet :  " << bullet << endl;
  }

  Gun& Gun::operator =(const Gun &rhs)
  {
    if (*this == rhs)
    {
      return *this;
    }
    gName = rhs.gName;
    bullet = rhs.bullet;
    return *this;
  }

  // Class GunFactory
  GunFactory::~GunFactory()
  {
    for (auto & it : gunPool)
    {
      delete it;
    }
    gunPool.clear();
  }

  GunFactory::GunFactory()
  {}

  Gun* GunFactory::GetGun(const char *name)
  {
    for (auto it = gunPool.begin(); it != gunPool.end(); it++) {
      if (**it == name)
        return *it;
    }
    Gun* tGun = new Gun(name);
    gunPool.push_back(tGun);
    return tGun;
  }

  // Class GunCheck
  GunCheck::~GunCheck()
  {}

  GunCheck::GunCheck(int n, const char *name) : no(n), gName(name)
  {}

  int GunCheck::GetNum()
  {
    return no;
  }

  void GunCheck::AddNum(int n)
  {
    no += n;
  }

  bool GunCheck::operator ==(const char *rhs)
  {
    if (strcmp(gName, rhs) == 0)
      return true;
    else
      return false;
  }

  // Class WeaponStore 
  WeaponStore::WeaponStore()
  {
    myFactory = new GunFactory();
  }

  WeaponStore::~WeaponStore()
  {
    delete myFactory;
    gunList.clear();
  }

  Gun* WeaponStore::AddGun(const char *name, int num)
  {
    bool exist = false;
    for (auto it = gunList.begin(); it != gunList.end(); it++) {
      if (*it == name)
      {
        (*it).AddNum(num);
        exist = true;
        break;
      }
    }
    if (!exist)
    {
      GunCheck mylist = GunCheck(num, name);
      gunList.push_back(mylist);
    }
    return(myFactory->GetGun(name));
  }

  Gun* WeaponStore::PickUp(const char *name, int bullet)
  {
    Gun* tGun = myFactory->GetGun(name);
    Gun* newGun = new Gun(*tGun);
    newGun->Load(bullet);
    return newGun;
  }

  void TestFlyweightPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    WeaponStore myStore = WeaponStore();
    Gun* myGun1 = myStore.AddGun("M4A1", 10);
    Gun* myGun2 = myStore.AddGun("AK47", 15);
    Gun* myGun3 = myStore.PickUp("M4A1", 70);
    Gun* myGun4 = myStore.PickUp("AK47", 90);
    myGun1->ShowMe();  // Guns in store
    myGun2->ShowMe();  // Guns in store
    myGun3->ShowMe();  // Particular gun I picked up
    myGun4->ShowMe();  // Particular gun I picked up
  }
}