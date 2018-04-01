#include "stdafx.h"
#include "ChainOfResponsibility.h"
#include <iostream>

namespace DemoChainOfResponsibility {
  Handler::Handler(Handler *pSuccessor) : m_pSuccessor(pSuccessor)
  {
  }

  Handler::~Handler()
  {
    delete m_pSuccessor;
    m_pSuccessor = NULL;
  }

  void ConcreateHandler1::HandleRequset()
  {
    if (NULL != m_pSuccessor)
    {
      m_pSuccessor->HandleRequset();
    }
    else
    {
      std::cout << "HandleRequset by ConcreateHandler1\n";
    }
  }

  void ConcreateHandler2::HandleRequset()
  {
    if (NULL != m_pSuccessor)
    {
      m_pSuccessor->HandleRequset();
    }
    else
    {
      std::cout << "HandleRequset by ConcreateHandler2\n";
    }
  }

  void TestChainOfResponsibility()
  {
    FUNC_INFO;
    Handler *p1 = new ConcreateHandler1();
    Handler *p2 = new ConcreateHandler2(p1);
    p2->HandleRequset();
    delete p2;
  }
}
