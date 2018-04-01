#include "stdafx.h"
#include "FlyWeight.h"
#include <iostream>

namespace DemoFlyWeightPattern {
  inline STATE Flyweight::GetIntrinsicState()
  {
    return m_State;
  }

  FlyweightFactory::~FlyweightFactory()
  {
    for (auto& it : m_listFlyweight)
    {
      delete it;
    }
    m_listFlyweight.clear();
  }

  Flyweight* FlyweightFactory::GetFlyweight(const STATE& key)
  {
    for (auto& it : m_listFlyweight)
    {
      if (it->GetIntrinsicState() == key)
      {
        std::cout << "The Flyweight:" << key << " already exits" << std::endl;
        return it;
      }
    }

    std::cout << "Creating a new Flyweight:" << key << std::endl;
    Flyweight* flyweight = new ConcreateFlyweight(key);
    m_listFlyweight.push_back(flyweight);
    return flyweight;
  }

  void ConcreateFlyweight::Operation(STATE& ExtrinsicState)
  {
    std::cout << "ConcreateFlyweight Operation" << std::endl;
  }

  void TestFlyWeightPattern()
  {
    FUNC_INFO;
    FlyweightFactory flyweightfactory;
    flyweightfactory.GetFlyweight("hello");
    flyweightfactory.GetFlyweight("world");
    flyweightfactory.GetFlyweight("hello");
  }
}