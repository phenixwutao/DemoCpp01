// DemoCpp01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SectionFileOperation.h"
#include "STLTemplateDemo.h"
#include "DemoClass.h"

using namespace UDemyDemo;
int main()
{
  printf("Welcome to C++!\n");
  //WriteFile();
  ReadFile();
  ParseFile();
  BinaryFile();
  VectorDemo();
  VectorCapacity();
  Vector2Dim(12);
  ListDemo();
  MapDemo();

  unsigned long ww = 100;
  printf("value ul is %ul\n", ww);
  printf("value lu is %lu\n", ww);

  DemoChild* aChild = new DemoChild;
  delete aChild;

  return EXIT_SUCCESS;
}

