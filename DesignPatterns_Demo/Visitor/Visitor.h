#pragma once
#ifndef VISITOR_H
#define VISITOR_H
namespace DemoVisitorPattern {
  class Visitor;

  class Element
  {
  public:
    virtual ~Element() {}
    virtual void Accept(Visitor &rVisitor) = 0;

  protected:
    Element() {}
  };

  class ConcreateElementA : public Element
  {
  public:
    virtual ~ConcreateElementA() {}
    virtual void Accept(Visitor &rVisitor) override;
  };

  class ConcreateElementB : public Element
  {
  public:
    virtual ~ConcreateElementB() {}
    virtual void Accept(Visitor &rVisitor) override;
  };

  class Visitor
  {
  public:
    virtual ~Visitor() {}
    virtual void VisitConcreateElementA(ConcreateElementA *pConcreateElementA) = 0;
    virtual void VisitConcreateElementB(ConcreateElementB *pConcreateElementB) = 0;

  protected:
    Visitor() {}
  };

  class ConcreateVisitorA : public Visitor
  {
  public:
    virtual ~ConcreateVisitorA() {}

    virtual void VisitConcreateElementA(ConcreateElementA *pConcreateElementA) override;
    virtual void VisitConcreateElementB(ConcreateElementB *pConcreateElementB) override;
  };

  class ConcreateVisitorB : public Visitor
  {
  public:
    virtual ~ConcreateVisitorB() {}

    virtual void VisitConcreateElementA(ConcreateElementA *pConcreateElementA) override;
    virtual void VisitConcreateElementB(ConcreateElementB *pConcreateElementB) override;
  };
  void TestVisitorPattern();
}
#endif
 