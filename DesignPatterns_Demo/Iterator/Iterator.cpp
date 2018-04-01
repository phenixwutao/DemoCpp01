#include "stdafx.h"
#include <iostream>
#include "Iterator.h"

namespace DemoIteratorPattern {
  ConcreateAggregate::ConcreateAggregate(int nSize)
    : m_nSize(nSize), m_pData(nullptr)
  {
    m_pData = new DATA[m_nSize];

    for (int i = 0; i < nSize; ++i)
    {
      m_pData[i] = i;
    }
  }

  ConcreateAggregate::~ConcreateAggregate()
  {
    delete[] m_pData;
    m_pData = nullptr;
  }

  Iterater* ConcreateAggregate::CreateIterater(Aggregate *pAggregate)
  {
    return new ConcreateIterater(pAggregate);
  }

  int ConcreateAggregate::GetSize() const
  {
    return m_nSize;
  }

  DATA ConcreateAggregate::GetItem(int nIndex) const
  {
    if (nIndex < m_nSize && nIndex >= 0)
    {
      return m_pData[nIndex];
    }
    else
    {
      return -1;
    }
  }

  ConcreateIterater::ConcreateIterater(Aggregate* pAggregate)
    : m_pConcreateAggregate(pAggregate) , m_nIndex(0)
  {
  }

  void ConcreateIterater::First()
  {
    m_nIndex = 0;
  }

  void ConcreateIterater::Next()
  {
    if (m_nIndex < m_pConcreateAggregate->GetSize())
    {
      ++m_nIndex;
    }
  }

  bool ConcreateIterater::IsDone() const
  {
    return m_nIndex == m_pConcreateAggregate->GetSize();
  }

  DATA ConcreateIterater::CurrentItem() const
  {
    return m_pConcreateAggregate->GetItem(m_nIndex);
  }

  void TestIteratorPattern()
  {
    FUNC_INFO;
    Aggregate* pAggregate = new ConcreateAggregate(4);
    Iterater* pIterater = pAggregate->CreateIterater(pAggregate);
    //Iterater*  pIterater = new ConcreateIterater(pAggregate); // alternative

    for (; false == pIterater->IsDone(); pIterater->Next())
    {
      std::cout << "iterating item: " << pIterater->CurrentItem() << std::endl;
    }

    delete pIterater;
    delete pAggregate;
  }
}