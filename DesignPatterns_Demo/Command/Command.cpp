#include "stdafx.h"
#include "Command.h"
#include <iostream>

namespace DemoCommandPattern {
  void Receiver::Action()
  {
    std::cout << "Receiver Action\n";
  }

  Invoker::Invoker(Command *pCommand) : m_pCommand(pCommand)
  {
  }

  Invoker::~Invoker()
  {
    delete m_pCommand;
    m_pCommand = NULL;
  }

  void Invoker::Invoke()
  {
    if (NULL != m_pCommand)
    {
      m_pCommand->Execute();
    }
  }

  ConcreateComand::ConcreateComand(Receiver* pReceiver) : m_pReceiver(pReceiver)
  {
  }

  ConcreateComand::~ConcreateComand()
  {
    delete m_pReceiver;
    m_pReceiver = NULL;
  }

  void ConcreateComand::Execute()
  {
    if (NULL != m_pReceiver)
    {
      m_pReceiver->Action();
    }

    std::cout << "Execute by ConcreateComand\n";
  }

  void TestCommandPattern()
  {
    FUNC_INFO;
    auto pReceiver = new Receiver;
    Command* pCommand = new ConcreateComand(pReceiver);
    auto pInvoler = new Invoker(pCommand);
    pInvoler->Invoke();
    delete pInvoler;
  }
}