// DesignPatterns_Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AbstractFactory\AbstractFactory.h"
#include "Adapter\Adapter.h"
#include "Bridge\Bridge.h"
#include "Builder\Builder.h"
#include "ChainOfResponsibility\ChainOfResponsibility.h"
#include "Command\Command.h"
#include "Composite\Composite.h"
#include "Decorator\Decorator.h"
#include "Factory\Factory.h"
#include "FlyWeight\FlyWeight.h"
#include "Iterator\Iterator.h"
#include "Memento\Memento.h"
#include "Observer\Observer.h"

int main(int argc, char* argv[])
{
  DemoAbstractFactory::TestAbstractFactory();
  DemoAdapterPattern::TestAdapterPattern();
  DemoBridgePattern::TestBridgePattern();
  DemoBuilderPattern::TestBuilderPattern();
  DemoChainOfResponsibility::TestChainOfResponsibility();
  DemoCommandPattern::TestCommandPattern();
  DemoCompositePattern::TestCompositePattern();
  DemoDecoratorPattern::TestDecoratorPattern();
  DemoFactoryPattern::TestFactoryPattern();
  DemoFlyWeightPattern::TestFlyWeightPattern();
  DemoIteratorPattern::TestIteratorPattern();
  DemoMementoPattern::TestMementoPattern();
  DemoObserverPattern::TestObserverPattern();


  return 0;
}

