#pragma once

namespace Builder
{
  //Abstract product class
  class CarBreak {  // The break of car   
  public:
    virtual void Draw() = 0;
    virtual ~CarBreak() {}
  };

  class CarDoor {	 // The door of car   
  public:
    virtual void Draw() = 0;
    virtual ~CarDoor() {}
  };

  // Concrete product class
  class FordCarBreak : public CarBreak {
  public:
    void Draw();
    virtual ~FordCarBreak() {}
  };

  class FordCarDoor : public CarDoor {
  public:
    void Draw();
    virtual ~FordCarDoor() {}
  };

  class RollsCarBreak : public CarBreak {
  public:
    void Draw();
    virtual ~RollsCarBreak() {}
  };

  class RollsCarDoor : public CarDoor {
  public:
    void Draw();
    virtual ~RollsCarDoor() {}
  };

  class Car {
  public:
    Car();
    virtual ~Car();
    CarBreak * carBreak = nullptr;
    CarDoor* carDoor = nullptr;
  };

  // Abstract Builder
  class CarBuilder {
  public:
    virtual void CreatCar() = 0;
    virtual void CreatCarBreak() = 0;
    virtual void CreatCarDoor() = 0;
    virtual Car* GetCar() = 0;
    virtual ~CarBuilder() {}

  protected:
    Car * myCar;
    CarBuilder();
  };

  // Concrete Builder
  class FordCarBuilder : public CarBuilder {
  public:
    FordCarBuilder();
    void CreatCar();
    void CreatCarBreak();
    void CreatCarDoor();
    Car* GetCar();
    virtual ~FordCarBuilder() {}
  };

  class RollsCarBuilder : public CarBuilder {
  public:
    RollsCarBuilder();
    void CreatCar();
    void CreatCarBreak();
    void CreatCarDoor();
    Car* GetCar();
    virtual ~RollsCarBuilder() {};
  };

  // Director
  class CarMaker {
  public:
    static Car* MakeCar(CarBuilder& builder);
  };

  void TestBuilder();
}