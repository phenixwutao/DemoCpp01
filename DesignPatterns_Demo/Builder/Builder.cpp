#include "stdafx.h"
#include "Builder.h"
#include <iostream>
namespace DemoBuilderPattern {

  void ConcreateBuilder1::BuilderPartA()
  {
    std::cout << "BuilderPartA by ConcreateBuilder1\n";
  }

  void ConcreateBuilder1::BuilderPartB()
  {
    std::cout << "BuilderPartB by ConcreateBuilder1\n";
  }

  void ConcreateBuilder2::BuilderPartA()
  {
    std::cout << "BuilderPartA by ConcreateBuilder2\n";
  }

  void ConcreateBuilder2::BuilderPartB()
  {
    std::cout << "BuilderPartB by ConcreateBuilder2\n";
  }

  Director::Director(Builder* pBuilder) : m_pBuilder(pBuilder)
  {
  }

  Director::~Director()
  {
    delete m_pBuilder;
    m_pBuilder = nullptr;
  }

  void Director::Construct()
  {
    m_pBuilder->BuilderPartA();
    m_pBuilder->BuilderPartB();
  }
  void TestBuilderPattern()
  {
    FUNC_INFO;
    Builder* pBuilder1 = new ConcreateBuilder1;
    Director *pDirector1 = new Director(pBuilder1);
    pDirector1->Construct();

    Builder* pBuilder2 = new ConcreateBuilder2;
    Director *pDirector2 = new Director(pBuilder2);
    pDirector2->Construct();

    delete pDirector1;
    delete pDirector2;
  }
}
