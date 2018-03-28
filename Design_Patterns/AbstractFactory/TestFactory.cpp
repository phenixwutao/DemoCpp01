#include <StdAfx.h>

#include "CarFactory.h"
#include <memory>

void TestFactoryPattern()
{
  auto fac1 = std::make_unqiue<CarFactory>;
  CarFactory* carFactory;
  carFactory = new FordCarFactory;
  carFactory = new RollsCarFactory;
  CarBreak* myBreak = carFactory->CreatCarBreak();
  CarDoor*  myDoor = carFactory->CreatCarDoor();
  myBreak->Draw();
  myDoor->Draw();


}