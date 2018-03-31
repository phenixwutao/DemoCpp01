#pragma once
#include <iostream>
#include <list>
using namespace std;

namespace ObserverPattern {
  class Subject;

  class Observer {
  public:
    virtual ~Observer();
    virtual void Update(Subject* theChangedSubject) = 0;
  protected:
    Observer();
  };

  class Subject {
  protected:
    Subject();
  public:
    virtual ~Subject();
    virtual void Attach(Observer* tObserver);
    virtual void Detach(Observer* tObserver);
    virtual void Notify();
    virtual char* GetState();
  private:
    list<Observer*>* observerList;
  };

  class FamilyMember {
  public:
    FamilyMember(const char* name);
    virtual ~FamilyMember();
    const char* GetName();
  private:
    const char* myName;
  };

  class Mother : public FamilyMember, public Subject {
  public:
    Mother(const char* name);
    ~Mother();
    void Cook(char* dish);
    char* GetState();
  private:
    char* myDish;
  };

  class Child : public FamilyMember, public Observer {
  public:
    Child(const char* name);
    ~Child();
    virtual void Update(Subject* theChangedSubject);
  };
  void TestObserverPattern();
}