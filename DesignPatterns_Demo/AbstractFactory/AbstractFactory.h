#pragma once

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

namespace DemoAbstractFactory
{
  // abstract product A
  class AbstractProductA
  {
  public:
    AbstractProductA() {}
    virtual ~AbstractProductA() {}
  };

  // Concreate Product A1
  class ConcreateProductA1 : public AbstractProductA
  {
  public:
    ConcreateProductA1();
    virtual ~ConcreateProductA1();
  };

  // Concreate Product A2
  class ConcreateProductA2 : public AbstractProductA
  {
  public:
    ConcreateProductA2();
    virtual ~ConcreateProductA2();
  };

  // Abstract Product B
  class AbstractProductB
  {
  public:
    AbstractProductB() {}
    virtual ~AbstractProductB() {}
  };

  // Concreate Product B1
  class ConcreateProductB1 : public AbstractProductB
  {
  public:
    ConcreateProductB1();
    virtual ~ConcreateProductB1();
  };

  // Concreate Product B2
  class ConcreateProductB2 : public AbstractProductB
  {
  public:
    ConcreateProductB2();
    virtual ~ConcreateProductB2();
  };

  // Abstract Factory
  class AbstractFactory
  {
  public:
    AbstractFactory() {}
    virtual ~AbstractFactory() {}

    virtual AbstractProductA* CreateProductA() = 0;
    virtual AbstractProductB* CreateProductB() = 0;
  };

  // Concreate Factory1
  class ConcreateFactory1 : public AbstractFactory
  {
  public:
    ConcreateFactory1();
    virtual ~ConcreateFactory1();

    virtual AbstractProductA* CreateProductA();
    virtual AbstractProductB* CreateProductB();
  };

  // Concreate Factory2
  class ConcreateFactory2 : public AbstractFactory
  {
  public:
    ConcreateFactory2();
    virtual ~ConcreateFactory2();

    virtual AbstractProductA* CreateProductA();
    virtual AbstractProductB* CreateProductB();
  };
  void TestAbstractFactory();
}
#endif
