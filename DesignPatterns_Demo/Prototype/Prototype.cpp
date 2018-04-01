#include "stdafx.h"
#include "Prototype.h"
#include <iostream>

namespace DemoPrototypePattern {
  ConcreatePrototype1::ConcreatePrototype1()
  {
    std::cout << "construction of ConcreatePrototype1\n";
  }

  ConcreatePrototype1::~ConcreatePrototype1()
  {
    std::cout << "destruction of ConcreatePrototype1\n";
  }

  ConcreatePrototype1::ConcreatePrototype1(const ConcreatePrototype1&)
  {
    std::cout << "copy construction of ConcreatePrototype1\n";
  }

  Prototype* ConcreatePrototype1::Clone()
  {
    return new ConcreatePrototype1(*this);
  }

  ConcreatePrototype2::ConcreatePrototype2()
  {
    std::cout << "construction of ConcreatePrototype2\n";
  }

  ConcreatePrototype2::~ConcreatePrototype2()
  {
    std::cout << "destruction of ConcreatePrototype2\n";
  }

  ConcreatePrototype2::ConcreatePrototype2(const ConcreatePrototype2&)
  {
    std::cout << "copy construction of ConcreatePrototype2\n";
  }

  Prototype* ConcreatePrototype2::Clone()
  {
    return new ConcreatePrototype2(*this);
  }

  void TestPrototypePattern()
  {
    FUNC_INFO;
    Prototype* pPrototype1 = new ConcreatePrototype1();
    Prototype* pPrototype2 = pPrototype1->Clone();

    Prototype* pPrototype3 = new ConcreatePrototype2();
    Prototype* pPrototype4 = pPrototype3->Clone();

    delete pPrototype1;
    delete pPrototype2;
    delete pPrototype3;
    delete pPrototype4;
  }
}