#include "stdafx.h"
#include "State.h"
#include <iostream>

namespace DemoStatePattern {
  Context::Context(State* pState) : m_pState(pState)
  {
  }

  Context::~Context()
  {
    delete m_pState;
    m_pState = nullptr;
  }

  void Context::Request()
  {
    if (nullptr != m_pState)
    {
      m_pState->Handle(this);
    }
  }

  void Context::ChangeState(State *pState)
  {
    if (nullptr != m_pState)
    {
      delete m_pState;
      m_pState = nullptr;
    }

    m_pState = pState;
  }

  void ConcreateStateA::Handle(Context* pContext)
  {
    std::cout << "Handle by ConcreateStateA\n";

    if (NULL != pContext)
    {
      pContext->ChangeState(new ConcreateStateB());
    }
  }

  void ConcreateStateB::Handle(Context* pContext)
  {
    std::cout << "Handle by ConcreateStateB\n";

    if (NULL != pContext)
    {
      pContext->ChangeState(new ConcreateStateA());
    }
  }

  void TestStatePattern()
  {
    FUNC_INFO;
    State *pState = new ConcreateStateA();
    Context *pContext = new Context(pState);
    pContext->Request();
    pContext->Request();
    pContext->Request();

    delete pContext;
  }
}