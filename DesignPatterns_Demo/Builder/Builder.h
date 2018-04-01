#pragma once
#ifndef BUILDER_H
#define BUILDER_H

namespace DemoBuilderPattern {
  class Builder
  {
  public:
    Builder() {}
    virtual ~Builder() {}
    virtual void BuilderPartA() = 0;
    virtual void BuilderPartB() = 0;
  };

  class Director
  {
  public:
    Director(Builder* pBuilder);
    ~Director();
    void Construct();

  private:
    Builder * m_pBuilder;
  };

  class ConcreateBuilder1 : public Builder
  {
  public:
    ConcreateBuilder1() {}
    virtual ~ConcreateBuilder1() {}

    virtual void BuilderPartA() override;
    virtual void BuilderPartB() override;
  };

  class ConcreateBuilder2 : public Builder
  {
  public:
    ConcreateBuilder2() {}
    virtual ~ConcreateBuilder2() {}

    virtual void BuilderPartA() override;
    virtual void BuilderPartB() override;
  };
  void TestBuilderPattern();
}
#endif
