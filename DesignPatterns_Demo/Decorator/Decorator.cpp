#include "stdafx.h"
#include "Decorator.h"
#include <iostream>

namespace DemoDecoratorPattern {
  Decorator::~Decorator()
  {
    delete m_pComponent;
    m_pComponent = nullptr;
  }

  void ConcreateComponent::Operation()
  {
    std::cout << "Operation of ConcreateComponent\n";
  }

  void ConcreateDecorator::Operation()
  {
    m_pComponent->Operation();
    AddedBehavior();
  }

  void ConcreateDecorator::AddedBehavior()
  {
    std::cout << "AddedBehavior of ConcreateDecorator\n";
  }

  void TestDecoratorPattern()
  {
    FUNC_INFO;
    Component* pComponent = new ConcreateComponent;
    pComponent->Operation();
    Decorator* pDecorator = new ConcreateDecorator(pComponent);
    pDecorator->Operation();
    delete pDecorator;
  }
}