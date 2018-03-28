// Design_Patterns.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AbstractFactory\CarFactory.h"
#include "AdapterClass\AdapterClass.h"
#include "AdapterObject\AdapterObject.h"

int main()
{
  TestFactoryPattern();
  AdapterClass::TestAdapterClass();
  AdapterObject::TestAdapterObject();
  return 0;
}

