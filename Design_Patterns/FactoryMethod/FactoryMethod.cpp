#include "StdAfx.h"
#include "FactoryMethod.h"
#include <iostream>
using namespace std;

namespace FactoryMethodPattern
{
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
    carBreak = 0;
    carDoor = 0;
  }

  Car::~Car()
  {
    if (carBreak != nullptr)
    {
      delete carBreak;
      carBreak = 0;
    }
    if (carDoor != nullptr)
    {
      delete carDoor;
      carDoor = 0;
    }
  }

  Car* CarCreator::CreatCar(int ID)
  {
    Car* myCar = new Car;
    myCar->carBreak = CreatBreak(ID);
    myCar->carDoor = CreatDoor(ID);
    return myCar;
  }

  CarBreak* CarCreator::CreatBreak(int ID) const
  {
    if (ID == FORD)
      return new FordCarBreak;
    else if (ID == ROLLS)
      return new RollsCarBreak;
    else
      return nullptr;
  }

  CarDoor* CarCreator::CreatDoor(int ID) const
  {
    if (ID == FORD)
      return new FordCarDoor;
    else if (ID == ROLLS)
      return new RollsCarDoor;
    else
      return nullptr;
  }

  void TestFactoryMethodPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    CarCreator myCarCreator;
    Car* A = myCarCreator.CreatCar(FORD);
    Car* B = myCarCreator.CreatCar(ROLLS);
    A->carBreak->Draw();
    A->carDoor->Draw();
    B->carBreak->Draw();
    B->carDoor->Draw();
    delete A;
    delete B;
  }

}