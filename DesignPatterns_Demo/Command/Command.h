#pragma once
#ifndef COMMAND_H
#define COMMAND_H

namespace DemoCommandPattern {
  class Command
  {
  public:
    virtual ~Command() {}
    virtual void Execute() = 0;
  };

  class Receiver
  {
  public:
    void Action();
  };

  class Invoker
  {
  public:
    Invoker(Command *pCommand);
    ~Invoker();

    void Invoke();
  private:
    Command * m_pCommand;
  };

  class ConcreateComand : public Command
  {
  public:
    ConcreateComand(Receiver* pReceiver);
    virtual ~ConcreateComand();

    virtual void Execute() override;

  private:
    Receiver * m_pReceiver;
  };

  void TestCommandPattern();
}
#endif
