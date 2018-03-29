// Design_Patterns.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AbstractFactory\CarFactory.h"
#include "AdapterClass\AdapterClass.h"
#include "AdapterObject\AdapterObject.h"
#include "Bridge\Bridge.h"
#include "Builder\CarBuilder.h"

int main()
{
  TestFactoryPattern();
  AdapterClass::TestAdapterClass();
  AdapterObject::TestAdapterObject();
  Bridge::TestBridge();
  Builder::TestBuilder();

  return 0;
}

