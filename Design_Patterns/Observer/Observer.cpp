#include "StdAfx.h"
#include "Observer.h"
namespace ObserverPattern
{
  // Class Observer
  Observer::Observer()
  {
  }

  Observer::~Observer()
  {
  }

  // Class Subject
  Subject::~Subject()
  {
    if (observerList != nullptr && observerList->size() > 0)
    {
      for (auto& it : *observerList)
      {
        delete it;
        it = 0;
      }
    }
    delete observerList;
    observerList = nullptr;
  }

  void Subject::Attach(Observer* tObserver)
  {
    observerList->push_back(tObserver);
  }

  void Subject::Detach(Observer* tObserver)
  {
    observerList->remove(tObserver);
  }

  void Subject::Notify()
  {
    for (auto& it : (*observerList))
    {
      it->Update(this);
    }
  }

  Subject::Subject()
  {
    observerList = new list<Observer*>;
  }

  char* Subject::GetState()
  {
    return nullptr;
  }

  // Class FamilyMember
  FamilyMember::FamilyMember(const char* name) : myName(name)
  {
  }

  FamilyMember::~FamilyMember()
  {
  }

  const char* FamilyMember::GetName()
  {
    return myName;
  }

  // Class Mother
  Mother::Mother(const char* name) : FamilyMember(name)
  {
  }

  Mother::~Mother()
  {
  }

  void Mother::Cook(char* dish)
  {
    myDish = dish;
    cout << FamilyMember::GetName() << " has cooked " << myDish << "!" << endl;
    Notify();    // Call Notify
  }

  char* Mother::GetState()
  {
    return myDish;
  }

  // Class Child

  Child::Child(const char* name) : FamilyMember(name)
  {
  }

  Child::~Child()
  {
  }

  void Child::Update(Subject* theChangedSubject)
  {
    cout << FamilyMember::GetName() << " is eating " << theChangedSubject->GetState() << "!" << endl;
  }

  void TestObserverPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    Mother myMother("Angelica");
    Child* child1 = new Child("Lee");
    Child* child2 = new Child("Adam");
    myMother.Attach(child1);
    myMother.Attach(child2);
    std::string sDish("Pork in spicy soup");
    myMother.Cook(const_cast<char*>(sDish.c_str()));
  }
}