#include "stdafx.h"
#include "Observer.h"
#include <iostream>
#include <algorithm>

namespace DemoObserverPattern {

  void Subject::Attach(Observer *pObserver)
  {
    std::cout << "Attach an Observer\n";

    m_ListObserver.push_back(pObserver);
  }

  void Subject::Detach(Observer *pObserver)
  {
    auto iter = std::find(m_ListObserver.begin(), m_ListObserver.end(), pObserver);
    if (m_ListObserver.end() != iter)
    {
      m_ListObserver.erase(iter);
    }
    std::cout << "Detach an Observer\n";
  }

  void Subject::Notify()
  {
    std::cout << "Notify Observers's State\n";
    for (const auto& it : m_ListObserver)
    {
      it->Update(this);
    }
  }

  void Subject::SetState(STATE nState)
  {
    std::cout << "SetState By Subject " << nState << std::endl;
    m_nSubjectState = nState;
  }

  STATE Subject::GetState()
  {
    std::cout << "GetState By Subject " << m_nSubjectState  << std::endl;
    return m_nSubjectState;
  }

  Subject::~Subject()
  {
    for (auto& it : m_ListObserver)
    {
      delete it;
    }
    m_ListObserver.clear();
  }

  void ConcreateSubject::SetState(STATE nState)
  {
    std::cout << "SetState By ConcreateSubject " << nState << std::endl;
    m_nSubjectState = nState;
  }

  STATE ConcreateSubject::GetState()
  {
    std::cout << "GetState By ConcreateSubject " << m_nSubjectState << std::endl;
    return m_nSubjectState;
  }

  void ConcreateObserver::Update(Subject* pSubject)
  {
    if (nullptr == pSubject)
      return;

    m_nObserverState = pSubject->GetState();

    std::cout << "The ObeserverState is " << m_nObserverState << std::endl;
  }
  void TestObserverPattern()
  {
    FUNC_INFO;
    Observer *p1 = new ConcreateObserver;
    Observer *p2 = new ConcreateObserver;

    Subject* p = new ConcreateSubject;
    p->Attach(p1);
    p->Attach(p2);
    p->SetState(4);
    p->Notify();
    printf("------------------\n");

    p->Detach(p1);
    p->SetState(10);
    p->Notify();

    delete p;
  }
}