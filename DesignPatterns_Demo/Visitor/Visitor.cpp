#include "stdafx.h"
#include "Visitor.h"
#include <iostream>

namespace DemoVisitorPattern {
  void ConcreateElementA::Accept(Visitor &rVisitor)
  {
    rVisitor.VisitConcreateElementA(this);
  }

  void ConcreateElementB::Accept(Visitor &rVisitor)
  {
    rVisitor.VisitConcreateElementB(this);
  }

  void ConcreateVisitorA::VisitConcreateElementA(ConcreateElementA *pConcreateElementA)
  {
    std::cout << "VisitConcreateElementA By ConcreateVisitorA\n";
  }

  void ConcreateVisitorA::VisitConcreateElementB(ConcreateElementB *pConcreateElementA)
  {
    std::cout << "VisitConcreateElementB By ConcreateVisitorA\n";
  }

  void ConcreateVisitorB::VisitConcreateElementA(ConcreateElementA *pConcreateElementA)
  {
    std::cout << "VisitConcreateElementA By ConcreateVisitorB\n";
  }

  void ConcreateVisitorB::VisitConcreateElementB(ConcreateElementB *pConcreateElementA)
  {
    std::cout << "VisitConcreateElementB By ConcreateVisitorB\n";
  }

  void TestVisitorPattern()
  {
    FUNC_INFO;
    Visitor *pVisitorA = new ConcreateVisitorA;
    Element *pElement = new ConcreateElementA;
    pElement->Accept(*pVisitorA);

    delete pElement;
    delete pVisitorA;
  }
}