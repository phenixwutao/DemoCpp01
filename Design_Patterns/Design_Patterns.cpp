// Design_Patterns.cpp : Defines the entry point for the console application.
// The codes were copied from GitHub, maybe containing bugs, please report.

#include "stdafx.h"
#include "AbstractFactory\CarFactory.h"
#include "AdapterClass\AdapterClass.h"
#include "AdapterObject\AdapterObject.h"
#include "Bridge\Bridge.h"
#include "Builder\CarBuilder.h"
#include "ChainOfResponsibility\ChainOfResponsibility.h"
#include "Command\Command.h"
#include "Composite\Composite.h"
#include "Decorator\Decorator.h"
#include "Facade\Facade.h"
#include "FactoryMethod\FactoryMethod.h"
#include "Flyweight\Flyweight.h"
#include "Interpreter\Interpreter.h"
#include "Iterator\Iterator.h"
#include "Mediator\Mediator.h"
#include "Memento\Memento.h"
#include "Observer\Observer.h"
#include "Prototype\Prototype.h"
#include "Proxy\Proxy.h"
#include "Singleton\Singleton.h"
#include "State\State.h"
#include "Strategy\Strategy.h"
#include "TemplateMethod\TemplateMethod.h"
#include "Visitor\Visitor.h"

int main()
{
  TestFactoryPattern();
  AdapterClass::TestAdapterClass();
  AdapterObject::TestAdapterObject();
  Bridge::TestBridge();
  Builder::TestBuilder();
  ChainOfResponsibility::TestChainOfResponsibility();
  CommandPattern::TestCommandPattern();
  CompositePattern::TestCompositePattern();
  DecoratorPattern::TestDecoratorPattern();
  FacadePattern::TestFacadePattern();
  FactoryMethodPattern::TestFactoryMethodPattern();
  FlyweightPattern::TestFlyweightPattern();
  //InterpreterPattern::TestInterpreterPattern();
  IteratorPattern::TestIteratorPattern();
  MediatorPattern::TestMediatorPattern();
  MementoPattern::TestMementoPattern();
  ObserverPattern::TestObserverPattern();
  PrototypePattern::TestPrototypePattern();
  ProxyPattern::TestProxyPattern();
  SingletonPattern::TestSingletonPattern();
  StatePattern::TestStatePattern();
  StrategyPattern::TestStrategyPattern();
  TemplateMethod::TestTemplateMethod();
  VisitorPattern::TestVisitorPattern();

  return 0;
}

