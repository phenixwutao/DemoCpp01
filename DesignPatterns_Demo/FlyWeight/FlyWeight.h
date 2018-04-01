#pragma once
#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <string>
#include <list>
namespace DemoFlyWeightPattern {
  using STATE = std::string;

  class Flyweight
  {
  public:
    virtual ~Flyweight() {}

    STATE GetIntrinsicState();
    virtual void Operation(STATE& ExtrinsicState) = 0;

  protected:
    Flyweight(const STATE& state) : m_State(state)
    {
    }

  private:
    STATE m_State;
  };

  class FlyweightFactory
  {
  public:
    FlyweightFactory() {}
    ~FlyweightFactory();

    Flyweight* GetFlyweight(const STATE& key);

  private:
    std::list<Flyweight*>	m_listFlyweight;
  };

  class ConcreateFlyweight : public Flyweight
  {
  public:
    ConcreateFlyweight(const STATE& state) : Flyweight(state)
    {
    }
    virtual ~ConcreateFlyweight() {}

    virtual void Operation(STATE& ExtrinsicState);
  };
  void TestFlyWeightPattern();
}
#endif
