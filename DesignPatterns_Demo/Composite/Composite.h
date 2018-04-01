#pragma once
#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <list>

namespace DemoCompositePattern {
  class Component
  {
  public:
    Component() {}
    virtual ~Component() {}

    virtual void Operation() = 0;
    virtual void Add(Component* pChild);
    virtual void Remove(Component* pChild);
    virtual Component* GetChild(int nIndex);
  };

  class Leaf : public Component
  {
  public:
    Leaf() {}
    virtual ~Leaf() {}
    virtual void Operation() override;
  };

  class Composite : public Component
  {
  public:
    Composite() {}
    virtual ~Composite();

    virtual void Operation() override;

    virtual void Add(Component* pChild) override;
    virtual void Remove(Component* pChild) override;
    virtual Component* GetChild(int nIndex) override;

  private:
    std::list<Component*>	m_ListOfComponent;
  };
  void TestCompositePattern();
}
#endif