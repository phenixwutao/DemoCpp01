#pragma once

#include <list>
using namespace std;

namespace FlyweightPattern
{
  // Class Gun (Flyweight)
  class Gun {
  public:
    Gun(const char* name);
    Gun(const Gun& rhs);
    virtual ~Gun();

    void Load(int num);
    void ShowMe();
    bool operator == (const Gun& rhs);
    bool operator == (const char* rhs);
    Gun& operator = (const Gun& rhs);

  private:
    const char* gName;  // intrinsic
    int bullet;         // extrinsic
  };

  // Class GunFactory (FlyweightFactory)
  class GunFactory
  {
  public:
    GunFactory();
    virtual ~GunFactory();
    Gun* GetGun(const char* name);
  private:
    list<Gun*> gunPool;
  };

  // Class GunCheck
  class GunCheck
  {
  public:
    GunCheck(int n, const char* name);
    virtual ~GunCheck();
    int GetNum();
    void AddNum(int n);
    bool operator ==(const char* rhs);
  private:
    int no;
    const char* gName;
  };

  // Class WeaponStore (Client)
  class WeaponStore
  {
  public:
    WeaponStore();
    virtual ~WeaponStore();
    Gun* AddGun(const char* name, int num);
    Gun* PickUp(const char* name, int bullet);
  private:
    list<GunCheck> gunList;
    GunFactory* myFactory;
  };
  void TestFlyweightPattern();
}
