#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace MementoPattern {
  class Operation;
  class OperationMemento;

  // Class originator
  class Operation {
  public:
    Operation();
    ~Operation();
    void SetOperation(const string& tState);
    OperationMemento* StoreOperation();
    void RestoreOperation(OperationMemento* tMemento);
    void DisplayState();
  private:
    std::string state;
  };

  // Class Memento
  class OperationMemento {
  public:
    ~OperationMemento();
  private:
    friend class Operation;
    OperationMemento();
    void SetState(const string& tState);
    const string& GetState();

  private:
    std::string state;
  };

  // Class CareTaken
  class OperationCareTaken {
  public:
    OperationCareTaken(Operation* tOperation);
    ~OperationCareTaken();
    void Store();
    void Restore(int num);
  private:
    vector<OperationMemento*> operationList;
    Operation* careOperation;
  };
  void TestMementoPattern();
}