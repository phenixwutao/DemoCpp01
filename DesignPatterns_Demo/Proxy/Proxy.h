#pragma once
#ifndef PROXY_H
#define PROXY_H

namespace DemoProxyPattern {
  class Subject
  {
  public:
    Subject() {}
    virtual ~Subject() {}

    virtual void Request() = 0;
  };

  class RealSubject : public Subject
  {
  public:
    RealSubject();
    virtual ~RealSubject() {}

    virtual void Request() override;
  };

  class Proxy : public Subject
  {
  public:
    Proxy();
    virtual ~Proxy();

    virtual void Request() override;

  private:
    RealSubject * m_pRealSubject;
  };
  void TestProxyPattern();
}
#endif
