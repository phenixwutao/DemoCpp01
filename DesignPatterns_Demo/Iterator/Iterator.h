#pragma once
#ifndef ITERATOR_H
#define ITERATOR_H

namespace DemoIteratorPattern {
  typedef int DATA;

  class Iterater;

  class Aggregate
  {
  public:
    virtual ~Aggregate() {}

    virtual Iterater* CreateIterater(Aggregate *pAggregate) = 0;
    virtual int GetSize() const = 0;
    virtual DATA GetItem(int nIndex) const = 0;
  };

  class Iterater
  {
  public:
    virtual ~Iterater() {}

    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual DATA CurrentItem() const = 0;
  };

  class ConcreateAggregate : public Aggregate
  {
  public:
    ConcreateAggregate(int nSize);
    virtual ~ConcreateAggregate();

    virtual Iterater* CreateIterater(Aggregate *pAggregate) override;
    virtual int GetSize() const override;
    virtual DATA GetItem(int nIndex) const override;

  private:
    int   m_nSize;
    DATA* m_pData;
  };

  class ConcreateIterater : public Iterater
  {
  public:
    ConcreateIterater(Aggregate* pAggregate);
    virtual ~ConcreateIterater() {}

    virtual void First();
    virtual void Next();
    virtual bool IsDone() const override;
    virtual DATA CurrentItem() const override;

  private:
    Aggregate*  m_pConcreateAggregate;
    int			    m_nIndex;
  };
  void TestIteratorPattern();
}
#endif
