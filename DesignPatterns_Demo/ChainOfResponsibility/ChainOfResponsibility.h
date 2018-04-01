#pragma once
#ifndef CHAINOFRESPONSIBILITY_H
#define CHAINOFRESPONSIBILITY_H

#include <stdio.h>
namespace DemoChainOfResponsibility {
  class Handler
  {
  public:
    Handler(Handler *pSuccessor = NULL);
    virtual ~Handler();

    virtual void HandleRequset() = 0;

  protected:
    Handler * m_pSuccessor;
  };

  class ConcreateHandler1 : public Handler
  {
  public:
    ConcreateHandler1(Handler *pSuccessor = NULL) : Handler(pSuccessor) {}
    virtual ~ConcreateHandler1() {}

    virtual void HandleRequset() override;
  };

  class ConcreateHandler2 : public Handler
  {
  public:
    ConcreateHandler2(Handler *pSuccessor = NULL) : Handler(pSuccessor) {}
    virtual ~ConcreateHandler2() {}

    virtual void HandleRequset() override;
  };
  void TestChainOfResponsibility();
}
#endif
