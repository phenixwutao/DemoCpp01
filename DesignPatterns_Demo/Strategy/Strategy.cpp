#include "stdafx.h"
#include <iostream>
#include "Strategy.h"

namespace DemoStrategyPattern {

  Context::Context(Strategy *pStrategy) : m_pStrategy(pStrategy)
  {
  }

  Context::~Context()
  {
    delete m_pStrategy;
    m_pStrategy = nullptr;
  }

  void Context::ContextInterface()
  {
    if (nullptr != m_pStrategy)
    {
      m_pStrategy->AlgorithmInterface();
    }
  }

  void ConcreateStrategyA::AlgorithmInterface()
  {
    std::cout << "AlgorithmInterface Implemented by ConcreateStrategyA\n";
  }
  
  void TestStrategyPattern()
  {
    FUNC_INFO;
    Strategy* pStrategy = new ConcreateStrategyA;
    Context*  pContext = new Context(pStrategy);
    pContext->ContextInterface();
    delete pContext;
  }
}