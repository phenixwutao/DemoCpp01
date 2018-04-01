#include "stdafx.h"
#include "Adapter.h"
#include <iostream>

namespace DemoAdapterPattern {
  void Adaptee::SpecialRequest()
  {
    std::cout << "SpecialRequest of Adaptee\n";
  }

  Adapter::Adapter(Adaptee* pAdaptee) : m_pAdptee(pAdaptee)
  {
  }

  Adapter::~Adapter()
  {
    delete m_pAdptee;
    m_pAdptee = nullptr;
  }

  void Adapter::Request()
  {
    std::cout << "Request of Adapter\n";
    m_pAdptee->SpecialRequest();
  }

  void TestAdapterPattern()
  {
    FUNC_INFO;
    Adaptee *pAdaptee = new Adaptee;
    Target *pTarget = new Adapter(pAdaptee);
    pTarget->Request();

    delete pTarget;
  }
}