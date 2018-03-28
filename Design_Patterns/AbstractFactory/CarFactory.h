#pragma once

//Abstract product class
class CarBreak   // The break of car   
{
public:
  virtual void Draw() = 0;
  virtual ~CarBreak() {}
};

class CarDoor	 // The door of car   
{
public:
  virtual void Draw() = 0;
  virtual ~CarDoor() {}
};

// Concrete product class
class FordCarBreak : public CarBreak
{
public:
  FordCarBreak();
  ~FordCarBreak();
  void Draw();
};

class FordCarDoor : public CarDoor
{
public:
  FordCarDoor();
  ~FordCarDoor();
  void Draw();
};

class RollsCarBreak : public CarBreak
{
public:
  RollsCarBreak();
  ~RollsCarBreak();
  void Draw();
};

class RollsCarDoor : public CarDoor
{
public:
  RollsCarDoor();
  ~RollsCarDoor();
  void Draw();
};

//Abstract Factory
class CarFactory
{
public:
  virtual CarBreak* CreatCarBreak() = 0;
  virtual CarDoor* CreatCarDoor() = 0;
  virtual ~CarFactory() {}
};

//Concrete Factory
class FordCarFactory : public CarFactory
{
public:
  FordCarFactory();
  ~FordCarFactory();
  FordCarBreak * CreatCarBreak();
  FordCarDoor* CreatCarDoor();
};

class RollsCarFactory : public CarFactory
{
public:
  RollsCarFactory();
  ~RollsCarFactory();
  RollsCarBreak * CreatCarBreak();
  RollsCarDoor* CreatCarDoor();
};

void TestFactoryPattern();
