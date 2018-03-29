// Design_Patterns.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AbstractFactory\CarFactory.h"
#include "AdapterClass\AdapterClass.h"
#include "AdapterObject\AdapterObject.h"
#include "Bridge\Bridge.h"
#include "Builder\CarBuilder.h"
#include "ChainOfResponsibility\ChainOfResponsibility.h"
#include "Command\Command.h"

int main()
{
  TestFactoryPattern();
  AdapterClass::TestAdapterClass();
  AdapterObject::TestAdapterObject();
  Bridge::TestBridge();
  Builder::TestBuilder();
  ChainOfResponsibility::TestChainOfResponsibility();
  CommandPattern::TestCommandPattern();

  return 0;
}

