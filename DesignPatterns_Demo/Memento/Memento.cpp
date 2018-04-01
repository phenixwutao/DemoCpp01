#include "stdafx.h"
#include "Memento.h"
#include <iostream>

namespace DemoMementoPattern {
  Originator::Originator()
  {
  }

  Originator::Originator(const State& rState) : m_State(rState)
  {
  }

  Originator::~Originator()
  {
  }

  State Originator::GetState()
  {
    return m_State;
  }

  void Originator::SetState(const State& rState)
  {
    m_State = rState;
  }

  Memento* Originator::CreateMemento()
  {
    return new Memento(m_State);
  }

  void Originator::RestoreState(Memento* pMemento)
  {
    if (NULL != pMemento)
    {
      m_State = pMemento->GetState();
    }
  }

  void Originator::PrintState()
  {
    std::cout << "State = " << m_State << std::endl;
  }

  Memento::Memento(const State& rState) : m_State(rState)
  {
  }

  State Memento::GetState()
  {
    return m_State;
  }

  void Memento::SetState(const State& rState)
  {
    m_State = rState;
  }

  void TestMementoPattern()
  {
    FUNC_INFO;
    Originator* pOriginator = new Originator("old state");
    pOriginator->PrintState();

    Memento *pMemento = pOriginator->CreateMemento();

    pOriginator->SetState("new state");
    pOriginator->PrintState();

    pOriginator->RestoreState(pMemento);
    pOriginator->PrintState();

    delete pOriginator;
    delete pMemento;
  }
}