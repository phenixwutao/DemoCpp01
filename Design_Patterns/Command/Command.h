#pragma once
#include <list>

namespace CommandPattern {
  // Receiver 
  class HouseWife {
  public:
    HouseWife(const char* name);
    ~HouseWife();
    void Cook(const char* dish);
    void Clean(int roomNo);
    void Wash(int clothNo);
  private:
    const char* myName;
  };


  // Abstract Command
  class Command {
  public:
    virtual ~Command();
    virtual void Execute() = 0;
  protected:
    Command();
  };

  // Concrete Commands
  class Cook : public Command {
  public:
    virtual ~Cook();
    Cook(HouseWife* tReciever, const char* dish);
    virtual void Execute();
  private:
    HouseWife * reciever;
    const char* myDish;
  };

  class Clean : public Command {
  public:
    virtual ~Clean();
    Clean(HouseWife* tReciever, int tRoomNo);
    virtual void Execute();
  private:
    HouseWife * reciever;
    int roomNo;
  };

  class Wash : public Command {
  public:
    virtual ~Wash();
    Wash(HouseWife* tReciever, int tClothNo);
    virtual void Execute();
  private:
    HouseWife * reciever;
    int clothNo;
  };


  // MicroCommand  A list of Command
  class MicroCommand : public Command {
  public:
    MicroCommand();
    virtual ~MicroCommand();
    void Add(Command* tCommond);
    void Remove(Command* tCommand);
    virtual void Execute();

  private:
    std::list<Command*> myCommandList;
  };

  void TestCommandPattern();
}