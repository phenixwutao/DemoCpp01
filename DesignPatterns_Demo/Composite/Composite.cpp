#include "stdafx.h"
#include "Composite.h"
#include <iostream>
#include <algorithm>

namespace DemoCompositePattern {
  void Component::Add(Component* pChild)
  {
  }

  void Component::Remove(Component* pChild)
  {
  }

  Component* Component::GetChild(int nIndex)
  {
    return nullptr;
  }

  void Leaf::Operation()
  {
    std::cout << "Operation by leaf\n";
  }

  Composite::~Composite()
  {
    for (auto& it : m_ListOfComponent)
    {
      delete it;
    }
    m_ListOfComponent.clear();
  }

  void Composite::Add(Component* pChild)
  {
    m_ListOfComponent.push_back(pChild);
  }

  void Composite::Remove(Component* pChild)
  {
    auto iter = std::find(m_ListOfComponent.begin(), m_ListOfComponent.end(), pChild);

    if (m_ListOfComponent.end() != iter)
    {
      m_ListOfComponent.erase(iter);
    }
  }

  Component* Composite::GetChild(int nIndex)
  {
    if (nIndex <= 0 || nIndex > m_ListOfComponent.size())
      return nullptr;
    else
    {
      int i = 1;
      for (const auto& it : m_ListOfComponent)
      {
        if (i == nIndex)
        {
          printf("Child %d\n", i);
          return it;
        }
        i++;
      }
      return nullptr;
    }
  }

  void Composite::Operation()
  {
    std::cout << "Operation by Composite\n";
    for (const auto& it : m_ListOfComponent)
    {
      it->Operation();
    }
  }

  void TestCompositePattern()
  {
    FUNC_INFO;
    Leaf *pLeaf1 = new Leaf;
    Leaf *pLeaf2 = new Leaf;

    Composite* pComposite = new Composite;
    pComposite->Add(pLeaf1);
    pComposite->Add(pLeaf2);
    pComposite->Operation();
    pComposite->GetChild(2)->Operation();

    delete pComposite;
  }
}