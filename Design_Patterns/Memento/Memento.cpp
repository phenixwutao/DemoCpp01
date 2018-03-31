#include "StdAfx.h"
#include "Memento.h"
namespace MementoPattern {

  // Class originator
  Operation::Operation()
  {
  }

  Operation::~Operation() {

  }

  void Operation::SetOperation(const string& tState)
  {
    state = tState;
  }

  OperationMemento* Operation::StoreOperation()
  {
    OperationMemento* tMemento = new OperationMemento();
    tMemento->SetState(state);
    return tMemento;
  }

  void Operation::RestoreOperation(OperationMemento* tMemento)
  {
    state = tMemento->GetState();
  }

  void Operation::DisplayState()
  {
    cout << state << endl;
  }

  // Class Memento
  OperationMemento::~OperationMemento()
  {
  }

  OperationMemento::OperationMemento()
  {
  }

  void OperationMemento::SetState(const string& tState)
  {
    state = tState;
  }

  const string& OperationMemento::GetState()
  {
    return state;
  }

  // Class CareTaken
  OperationCareTaken::OperationCareTaken(Operation* tOperation) : careOperation(tOperation)
  {
  }

  OperationCareTaken::~OperationCareTaken()
  {
    //release the memory and clean the list
    if (operationList.size() > 0)
    {
      for (auto& it : operationList)
      {
        delete it;
      }
    operationList.clear();
    }
  }

  void OperationCareTaken::Store()
  {
    OperationMemento* tMemento = careOperation->StoreOperation();
    operationList.push_back(tMemento);
  }

  void OperationCareTaken::Restore(int num)
  {
    if (num >= operationList.size())
    {
      cout << "Can't do the restore!" << endl;
    }
    else {
      careOperation->RestoreOperation(operationList[operationList.size() - 1 - num]);
    }
  }
  void TestMementoPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    Operation* myOperation = new Operation();
    OperationCareTaken myCareTaken = OperationCareTaken(myOperation);
    myOperation->SetOperation("Get Up!");
    myCareTaken.Store();
    myOperation->SetOperation("Toothbrushing!");
    myCareTaken.Store();
    myOperation->SetOperation("Face Washing!");
    myCareTaken.Store();
    myOperation->SetOperation("Cook Breakfast!");
    myCareTaken.Store();
    myOperation->SetOperation("Have a breakfast!");
    myCareTaken.Store();
    myOperation->SetOperation("Go for working!");
    myCareTaken.Store();
    myOperation->DisplayState();
    myCareTaken.Restore(5);
    myOperation->DisplayState();
    delete myOperation;
  }
}
