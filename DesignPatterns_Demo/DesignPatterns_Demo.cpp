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

int main(int argc, char* argv[])
{
  DemoAbstractFactory::TestAbstractFactory();
  DemoAdapterPattern::TestAdapterPattern();
  DemoBridgePattern::TestBridgePattern();
  DemoBuilderPattern::TestBuilderPattern();
  DemoChainOfResponsibility::TestChainOfResponsibility();
  DemoCommandPattern::TestCommandPattern();
  DemoCompositePattern::TestCompositePattern();

  return 0;
}

