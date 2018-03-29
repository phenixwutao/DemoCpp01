#include "StdAfx.h"
#include "Command.h"
#include <iostream>
using namespace std;

namespace CommandPattern {
  // Receiver Class
  HouseWife::HouseWife(const char* name) : myName(name)
  {
  }

  HouseWife::~HouseWife()
  {}

  void HouseWife::Cook(const char* dish)
  {
    cout << myName << " has cooked " << dish << "!" << endl;
  }

  void HouseWife::Clean(int roomNo)
  {
    if (roomNo == 1) {
      cout << myName << " has cleaned living room!" << endl;
    }
    else if (roomNo == 2) {
      cout << myName << " has cleaned dining room!" << endl;
    }
    else if (roomNo == 3) {
      cout << myName << " has cleaned bedroom!" << endl;
    }
  }

  void HouseWife::Wash(int clothNo)
  {
    cout << myName << " has washed " << clothNo << " cloth!" << endl;
  }


  // Class Command
  Command::~Command()
  {
  }

  Command::Command()
  {
  }

  // Class Cook
  Cook::~Cook()
  {
    //delete reciever;
  }

  Cook::Cook(HouseWife* tReciever, const char* dish)
    : reciever(tReciever), myDish(dish)
  {
  }

  void Cook::Execute()
  {
    reciever->Cook(myDish);
  }


  // Class Clean
  Clean::~Clean()
  {
    //delete reciever;
  }

  Clean::Clean(HouseWife* tReciever, int tRoomNo)
    : reciever(tReciever), roomNo(tRoomNo)
  {
  }

  void Clean::Execute()
  {
    reciever->Clean(roomNo);
  }


  // Class Wash
  Wash::~Wash()
  {
    //delete reciever;
  }

  Wash::Wash(HouseWife* tReciever, int tClothNo)
    : reciever(tReciever), clothNo(tClothNo)
  {
  }

  void Wash::Execute()
  {
    reciever->Wash(clothNo);
  }


  // Class MicroCommand
  MicroCommand::~MicroCommand()
  {
    //for (auto& it : myCommandList)
    //{
    //  delete it;
    //}
    list<Command*>::const_iterator it;
    for (it = myCommandList.begin(); it != myCommandList.end(); it++)
    {
      delete *it;
    }
    myCommandList.clear();
  }

  MicroCommand::MicroCommand()
  {
  }

  void MicroCommand::Add(Command* tCommond)
  {
    myCommandList.push_back(tCommond);
  }

  void MicroCommand::Remove(Command* tCommand)
  {
    myCommandList.remove(tCommand);
  }

  void MicroCommand::Execute()
  {
    for (auto& it : myCommandList)
    {
      it->Execute();
    }
  }

  void TestCommandPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    HouseWife* wife = new HouseWife("Wife Li");
    HouseWife* mother = new HouseWife("Mother");
    Command* myCommand1 = new Cook(wife, "fish");
    Command* myCommand2 = new Clean(wife, 2);
    Command* myCommand3 = new Wash(mother, 5);
    MicroCommand commands = MicroCommand();
    commands.Add(myCommand1);
    commands.Add(myCommand2);
    commands.Add(myCommand3);
    commands.Execute();
    delete wife;
    delete mother;
  }
}
