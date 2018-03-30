#pragma once

namespace FactoryMethodPattern
{

#define FORD 1
#define ROLLS 2

  //Abstract product class
  class CarBreak {  // The break of car   
  public:
    ~CarBreak() {}
    virtual void Draw() = 0;
  };

  class CarDoor {	 // The door of car   
  public:
    ~CarDoor() {}
    virtual void Draw() = 0;
  };

  // Concrete product class
  class FordCarBreak : public CarBreak
  {
  public:
    void Draw();
  };

  class FordCarDoor : public CarDoor
  {
  public:
    void Draw();
  };

  class RollsCarBreak : public CarBreak
  {
  public:
    void Draw();
  };

  class RollsCarDoor : public CarDoor
  {
  public:
    void Draw();
  };

  class Car {
  public:
    Car();
    ~Car();
    CarBreak * carBreak;
    CarDoor* carDoor;
  };

  // Creator
  class CarCreator {
  public:
    virtual ~CarCreator() {}
    Car * CreatCar(int ID);

    // Factory Method
    virtual CarBreak* CreatBreak(int ID) const;
    virtual CarDoor*  CreatDoor(int ID) const;
  };

  //class FordCarCreator : public CarCreator{
  //public:
  //	virtual CarBreak* CreatBreak() = 0;
  //	virtual CarDoor* CreatCarDoor() = 0;
  //};
  //
  //class RollsCarCreator : public CarCreator{
  //public:
  //	virtual CarBreak* CreatBreak() = 0;
  //	virtual CarDoor* CreatCarDoor() = 0;
  //};

  void TestFactoryMethodPattern();
}