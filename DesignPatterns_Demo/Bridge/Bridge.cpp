#include "stdafx.h"
#include "Bridge.h"
#include <iostream>

namespace DemoBridgePattern {
  void ConcreateImplementorA::OperationImpl()
  {
    std::cout << "Implementation by ConcreateImplementorA\n";
  }

  void ConcreateImplementorB::OperationImpl()
  {
    std::cout << "Implementation by ConcreateImplementorB\n";
  }

  Abstraction::Abstraction(Implementor* pImplementor) : m_pImplementor(pImplementor)
  {
  }

  Abstraction::~Abstraction()
  {
    delete m_pImplementor;
    m_pImplementor = nullptr;
  }

  void Abstraction::Operation()
  {
    m_pImplementor->OperationImpl();
  }

  void TestBridgePattern()
  {
    FUNC_INFO;
    ConcreateImplementorA *pImplA = new ConcreateImplementorA();
    Abstraction *pAbstraction1 = new Abstraction(pImplA);
    pAbstraction1->Operation();

    ConcreateImplementorB *pImplB = new ConcreateImplementorB();
    Abstraction *pAbstraction2 = new Abstraction(pImplB);
    pAbstraction2->Operation();

    delete pAbstraction1;
    delete pAbstraction2;
  }
}