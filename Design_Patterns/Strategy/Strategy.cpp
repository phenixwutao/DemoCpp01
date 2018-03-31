#include "StdAfx.h"
#include "Strategy.h"
namespace StrategyPattern {

  // Class KongfuMan
  KongfuMan::KongfuMan(const char* name) : myName(name)
  {
    myKongfu = new Kongfu(this);
  }

  KongfuMan::~KongfuMan()
  {
    delete myKongfu;
  }

  void KongfuMan::Attack()
  {
    myKongfu->Attack();
  }

  void KongfuMan::ChangeKongfu(Kongfu* newKongfu) {
    delete myKongfu;
    myKongfu = newKongfu;
  }

  const char* KongfuMan::GetName()
  {
    return myName;
  }


  // Class Kongfu
  Kongfu::Kongfu(KongfuMan* tMan) : myKongfuMan(tMan)
  {
  }

  Kongfu::~Kongfu()
  {
    //delete myKongfuMan;
  }

  void Kongfu::Attack()
  {
    cout << myKongfuMan->GetName() << ": Show basic kong fu!" << endl;
  }

  // Class Wing Chun
  WingChun::WingChun(KongfuMan* tMan) : Kongfu(tMan)
  {
  }

  WingChun::~WingChun()
  {
  }

  void WingChun::Attack()
  {
    cout << myKongfuMan->GetName() << ": Show Wing Chun!" << endl;
  }

  // Class Taiji
  Taiji::Taiji(KongfuMan* tMan) : Kongfu(tMan)
  {
  }

  Taiji::~Taiji()
  {
  }

  void Taiji::Attack()
  {
    cout << myKongfuMan->GetName() << ": Show Tai Ji!" << endl;
  }

  // Class Shao Lin
  Shaolin::Shaolin(KongfuMan* tMan) : Kongfu(tMan)
  {
  }

  Shaolin::~Shaolin()
  {
  }

  void Shaolin::Attack()
  {
    cout << myKongfuMan->GetName() << ": Show Shao lin kongfu!" << endl;
  }

  void TestStrategyPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    KongfuMan* master1 = new KongfuMan("Zenny");
    KongfuMan* master2 = new KongfuMan("Yee");
    KongfuMan* master3 = new KongfuMan("Fang");
    master1->ChangeKongfu(new Taiji(master1));
    master2->ChangeKongfu(new WingChun(master2));
    master3->ChangeKongfu(new Shaolin(master3));
    master1->Attack();
    master2->Attack();
    master3->Attack();
    delete master1;
    delete master2;
    delete master3;
  }
}