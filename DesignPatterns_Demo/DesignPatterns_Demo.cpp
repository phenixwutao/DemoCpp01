// DesignPatterns_Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AbstractFactory\AbstractFactory.h"
#include "Adapter\Adapter.h"
#include "Bridge\Bridge.h"

int main(int argc, char* argv[])
{
  DemoAbstractFactory::TestAbstractFactory();
  DemoAdapterPattern::TestAdapterPattern();
  DemoBridgePattern::TestBridgePattern();

  return 0;
}

