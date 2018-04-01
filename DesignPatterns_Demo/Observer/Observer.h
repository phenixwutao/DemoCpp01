#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H
#include <list>

namespace DemoObserverPattern {
  using STATE = int;
  class Observer;

  class Subject
  {
  public:
    Subject() : m_nSubjectState(-1) {}
    virtual ~Subject();

    void Notify();
    void Attach(Observer *pObserver);
    void Detach(Observer *pObserver);

    virtual void	SetState(STATE nState);
    virtual STATE	GetState();

  protected:
    STATE m_nSubjectState;
    std::list<Observer*>	m_ListObserver;
  };

  class Observer
  {
  public:
    Observer() : m_nObserverState(-1) {}
    virtual ~Observer() {}

    virtual void Update(Subject* pSubject) = 0;

  protected:
    STATE m_nObserverState;
  };

  class ConcreateSubject : public Subject
  {
  public:
    ConcreateSubject() : Subject() {}
    virtual ~ConcreateSubject() {}

    virtual void	SetState(STATE nState) override;
    virtual STATE	GetState() override;
  };

  class ConcreateObserver : public Observer
  {
  public:
    ConcreateObserver() : Observer() {}
    virtual ~ConcreateObserver() {}

    virtual void Update(Subject* pSubject) override;
  };
  void TestObserverPattern();
}
#endif
