#include "StdAfx.h"
#include <iostream>
#include "AbstractFactory.h"

namespace DemoAbstractFactory {
  ConcreateProductA1::ConcreateProductA1()
  {
    std::cout << "construction of ConcreateProductA1\n";
  }

  ConcreateProductA1::~ConcreateProductA1()
  {
    std::cout << "destruction of ConcreateProductA1\n";
  }

  ConcreateProductA2::ConcreateProductA2()
  {
    std::cout << "construction of ConcreateProductA2\n";
  }

  ConcreateProductA2::~ConcreateProductA2()
  {
    std::cout << "destruction of ConcreateProductA2\n";
  }

  ConcreateProductB1::ConcreateProductB1()
  {
    std::cout << "construction of ConcreateProductB1\n";
  }

  ConcreateProductB1::~ConcreateProductB1()
  {
    std::cout << "destruction of ConcreateProductB1\n";
  }

  ConcreateProductB2::ConcreateProductB2()
  {
    std::cout << "construction of ConcreateProductB2\n";
  }

  ConcreateProductB2::~ConcreateProductB2()
  {
    std::cout << "destruction of ConcreateProductB2\n";
  }

  ConcreateFactory1::ConcreateFactory1()
  {
    std::cout << "construction of ConcreateFactory1\n";
  }

  ConcreateFactory1::~ConcreateFactory1()
  {
    std::cout << "destruction of ConcreateFactory1\n";
  }

  AbstractProductA* ConcreateFactory1::CreateProductA()
  {
    return new ConcreateProductA1();
  }

  AbstractProductB* ConcreateFactory1::CreateProductB()
  {
    return new ConcreateProductB1();
  }

  ConcreateFactory2::ConcreateFactory2()
  {
    std::cout << "construction of ConcreateFactory2\n";
  }

  ConcreateFactory2::~ConcreateFactory2()
  {
    std::cout << "destruction of ConcreateFactory2\n";
  }

  AbstractProductA* ConcreateFactory2::CreateProductA()
  {
    return new ConcreateProductA2();
  }

  AbstractProductB* ConcreateFactory2::CreateProductB()
  {
    return new ConcreateProductB2();
  }
  void TestAbstractFactory()
  {
    FUNC_INFO;
    ConcreateFactory1 *pFactory1 = new ConcreateFactory1;
    AbstractProductA *pProductA1 = pFactory1->CreateProductA();
    AbstractProductB *pProductB1 = pFactory1->CreateProductB();
    delete pFactory1;
    delete pProductA1;
    delete pProductB1;

    ConcreateFactory2 *pFactory2 = new ConcreateFactory2;
    AbstractProductA *pProductA2 = pFactory2->CreateProductA();
    AbstractProductB *pProductB2 = pFactory2->CreateProductB();
    delete pFactory2;
    delete pProductA2;
    delete pProductB2;
  }
}