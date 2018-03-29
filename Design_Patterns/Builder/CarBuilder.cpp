#include "StdAfx.h"

#include "CarBuilder.h"
#include <iostream>
using namespace std;

namespace Builder {

  void FordCarBreak::Draw()
  {
    cout << "I am a car break of Ford! \n";
  }

  void FordCarDoor::Draw()
  {
    cout << "I am a car door of Ford! \n";
  }

  void RollsCarBreak::Draw()
  {
    cout << "I am a car break of Rollys-Royce! \n";
  }

  void RollsCarDoor::Draw()
  {
    cout << "I am a car door of Rollys-Royce! \n";
  }

  Car::Car()
  {
  }
  Car::~Car()
  {
    delete carBreak;
    delete carDoor;
  }

  Car* CarMaker::MakeCar(CarBuilder &builder) {
    builder.CreatCar();
    builder.CreatCarBreak();
    builder.CreatCarDoor();
    return builder.GetCar();
  }

  CarBuilder::CarBuilder() {}

  FordCarBuilder::FordCarBuilder()
  {
    myCar = 0;
  }

  void FordCarBuilder::CreatCar()
  {
    myCar = new Car;
  }

  void FordCarBuilder::CreatCarBreak()
  {
    FordCarBreak* myBreak = new FordCarBreak;
    myCar->carBreak = myBreak;
  }

  void FordCarBuilder::CreatCarDoor()
  {
    FordCarDoor* myDoor = new FordCarDoor;
    myCar->carDoor = myDoor;
  }

  Car* FordCarBuilder::GetCar()
  {
    return myCar;
  }

  RollsCarBuilder::RollsCarBuilder()
  {
    myCar = 0;
  }

  void RollsCarBuilder::CreatCar()
  {
    myCar = new Car;
  }

  void RollsCarBuilder::CreatCarBreak()
  {
    RollsCarBreak* myBreak = new RollsCarBreak;
    myCar->carBreak = myBreak;
  }

  void RollsCarBuilder::CreatCarDoor()
  {
    RollsCarDoor* myDoor = new RollsCarDoor;
    myCar->carDoor = myDoor;
  }

  Car* RollsCarBuilder::GetCar()
  {
    return myCar;
  }

  void TestBuilder()
  {
    printf("in %s\n", __func__);
    FordCarBuilder myFordCarBuilder;
    auto myCar1 = CarMaker::MakeCar(myFordCarBuilder);
    myCar1->carBreak->Draw();
    myCar1->carDoor->Draw();
    delete myCar1;

    RollsCarBuilder myRollsCarBuilder;
    auto myCar2 = CarMaker::MakeCar(myRollsCarBuilder);
    myCar2->carBreak->Draw();
    myCar2->carDoor->Draw();
    delete myCar2;
  }
}