#include "StdAfx.h"
#include "Decorator.h"
#include <iostream>
using namespace std;

namespace DecoratorPattern
{
  // Class Soldier 
  Soldier::~Soldier()
  {
    //delete sName;
  }

  void Soldier::ShowMe()
  {
    cout << "Name : " << sName << endl;
    cout << "Title: Soldier" << endl;
    cout << "Task :" << endl;
    cout << "       # Fight for freedom!" << endl;
  }

  Soldier::Soldier(const char *name) : sName(name)
  {}

  Soldier::Soldier() : sName("")
  {}

  const char* Soldier::GetName()
  {
    return sName;
  }

  // Class Pilot
  Pilot::~Pilot()
  {}

  void Pilot::ShowMe()
  {
    cout << "Name : " << GetName() << endl;
    cout << "Title: Pilot" << endl;
    cout << "Task :" << endl;
    cout << "       # Fight for freedom!" << endl;
  }

  Pilot::Pilot(const char *name) : Soldier(name)
  {}

  // Class Sailor
  Sailor::~Sailor()
  {}

  void Sailor::ShowMe()
  {
    cout << "Name : " << GetName() << endl;
    cout << "Title: Sailor" << endl;
    cout << "Task :" << endl;
    cout << "       # Fight for freedom!" << endl;
  }

  Sailor::Sailor(const char *name) : Soldier(name)
  {
  }

  // Class Decorator
  Decorator::Decorator(Soldier *tSoldier)
  {
    mySoldier = tSoldier;
  }

  Decorator::~Decorator()
  {
    delete mySoldier;
  }

  void Decorator::ShowMe()
  {
    mySoldier->ShowMe();
  }

  // Class FlyDecorator
  FlyDecorator::~FlyDecorator()
  {
  }

  FlyDecorator::FlyDecorator(Soldier *tSoldier) : Decorator(tSoldier)
  {}

  void FlyDecorator::ShowMe()
  {
    Decorator::ShowMe();
    cout << "       # Fly the plane!" << endl;
  }

  // Class SailDecorator
  SailDecorator::~SailDecorator()
  {
  }

  SailDecorator::SailDecorator(Soldier *tSoldier) : Decorator(tSoldier)
  {}

  void SailDecorator::ShowMe()
  {
    Decorator::ShowMe();
    cout << "       # Sail the warship!" << endl;
  }

  // Class ManageDecorator
  ManageDecorator::~ManageDecorator()
  {
  }

  ManageDecorator::ManageDecorator(Soldier *tSoldier) : Decorator(tSoldier)
  {
  }

  void ManageDecorator::ShowMe()
  {
    Decorator::ShowMe();
    cout << "       # Manage other soldiers!" << endl;
  }

  void TestDecoratorPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    Soldier* soldier1 = new SailDecorator(new Sailor("Adam"));
    Soldier* soldier2 = new FlyDecorator(new Pilot("Mark"));
    Soldier* soldier3 = new ManageDecorator(new SailDecorator(new Sailor("Martyn")));
    Soldier* soldier4 = new ManageDecorator(new FlyDecorator(new Pilot("Ostyne")));
    soldier1->ShowMe();
    soldier2->ShowMe();
    soldier3->ShowMe();
    soldier4->ShowMe();
    delete soldier1;
    delete soldier2;
    delete soldier3;
    delete soldier4;
  }
}
