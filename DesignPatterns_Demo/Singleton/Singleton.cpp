#include "stdafx.h"
#include "Singleton.h"
#include <iostream>

namespace DemoSingletonPattern {

  Singleton* Singleton::m_pStatic = NULL;

  Singleton* Singleton::GetInstancePtr()
  {
    if (nullptr == m_pStatic)
    {
      m_pStatic = new Singleton;
    }

    return m_pStatic;
  }

  Singleton Singleton::GetInstance()
  {
    return *GetInstancePtr();
  }

  void Singleton::Destroy(Singleton* p)
  {
    delete p;
  }

  void Singleton::Test()
  {
    std::cout << "Test!\n";
  }

  void TestSingletonPattern()
  {
    FUNC_INFO;
    auto pSingleton = Singleton::GetInstancePtr();
    pSingleton->Test();
    Singleton::Destroy(pSingleton);
  }
}