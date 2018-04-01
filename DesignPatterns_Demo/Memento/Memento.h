#pragma once
#ifndef MEMENTO_H
#define MEMENTO_H

#include <string>
namespace DemoMementoPattern {

  using State = std::string;
  class Memento;

  class Originator
  {
  public:
    Originator(const State& rState);
    Originator();
    ~Originator();

    Memento*	CreateMemento();
    //void		SetMemento(Memento* pMemento);
    State		GetState();
    void		SetState(const State& rState);
    void		RestoreState(Memento* pMemento);
    void		PrintState();

  private:
    State		m_State;
  };

  class Memento
  {
  private:
    friend class Originator;
    Memento(const State& rState);
    void	SetState(const State& rState);
    State	GetState();

    State	m_State;
  };
  void TestMementoPattern();
}
#endif
