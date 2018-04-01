#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H

namespace DemoStrategyPattern {
  class Strategy;

  class Context
  {
  public:
    Context(Strategy *pStrategy);
    ~Context();

    void ContextInterface();
  private:
    Strategy * m_pStrategy;
  };

  class Strategy
  {
  public:
    virtual ~Strategy() {}

    virtual void AlgorithmInterface() = 0;
  };

  class ConcreateStrategyA : public Strategy
  {
  public:
    virtual ~ConcreateStrategyA() {}

    virtual void AlgorithmInterface() override;
  };
  void TestStrategyPattern();
}
#endif
