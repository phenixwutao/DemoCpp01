#pragma once

#ifndef ADAPTER_H
#define ADAPTER_H

namespace DemoAdapterPattern {
  class Target
  {
  public:
    Target() {}
    virtual ~Target() {}
    virtual void Request() = 0;
  };

  class Adaptee
  {
  public:
    Adaptee() {}
    ~Adaptee() {}
    void SpecialRequest();
  };

  class Adapter : public Target
  {
  public:
    Adapter(Adaptee* pAdaptee);
    virtual ~Adapter();
    virtual void Request() override;

  private:
    Adaptee * m_pAdptee;
  };

  void TestAdapterPattern();
}
#endif
