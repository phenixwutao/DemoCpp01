#include "stdafx.h"
#include "Factory.h"
#include <iostream>
using namespace std;

namespace DemoFactoryPattern {
  ConcreateProduct::ConcreateProduct()
  {
    std::cout << "construction of ConcreateProduct\n";
  }

  ConcreateProduct::~ConcreateProduct()
  {
    std::cout << "destruction of ConcreateProduct\n";
  }

  void Creator::AnOperation()
  {
    Product* p = FactoryMethod();

    std::cout << "an operation of product\n";
    delete p; // possibly memory leak;
  }

  ConcreateCreator::ConcreateCreator()
  {
    std::cout << "construction of ConcreateCreator\n";
  }

  ConcreateCreator::~ConcreateCreator()
  {
    std::cout << "destruction of ConcreateCreator\n";
  }

  Product* ConcreateCreator::FactoryMethod()
  {
    return new ConcreateProduct();
  }
  void TestFactoryPattern()
  {
    FUNC_INFO;
    Creator *p = new ConcreateCreator;
    p->AnOperation();
    delete p;
  }
}