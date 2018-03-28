#include "StdAfx.h"

#include "CarFactory.h"

#include <iostream>
#include <memory>
using namespace std;

FordCarBreak::FordCarBreak()
{
  printf("in %s\n", __func__);
}

FordCarBreak::~FordCarBreak()
{
  printf("in %s\n", __func__);
}

void FordCarBreak::Draw()
{
	cout<<"I am a car break of Ford! \n";
}

FordCarDoor::FordCarDoor()
{
  printf("in %s\n", __func__);
}

FordCarDoor::~FordCarDoor()
{
  printf("in %s\n", __func__);
}

void FordCarDoor::Draw()
{
	cout<<"I am a car door of Ford! \n";
}

RollsCarBreak::RollsCarBreak() 
{
  printf("in %s\n", __func__);
}

RollsCarBreak::~RollsCarBreak()
{
  printf("in %s\n", __func__);
}

void RollsCarBreak::Draw()
{
	cout<<"I am a car break of Rollys-Royce! \n";
}

RollsCarDoor::RollsCarDoor()
{
  printf("in %s\n", __func__);
}

RollsCarDoor::~RollsCarDoor()
{
  printf("in %s\n", __func__);
}

void RollsCarDoor::Draw(){
	cout<<"I am a car door of Rollys-Royce! \n";
}

FordCarFactory::FordCarFactory()
{
  printf("in %s\n", __func__);
}

FordCarFactory::~FordCarFactory()
{
  printf("in %s\n", __func__);
}

FordCarBreak* FordCarFactory::CreatCarBreak()
{
	return new FordCarBreak;
}

FordCarDoor* FordCarFactory::CreatCarDoor()
{
	return new FordCarDoor;
}

RollsCarFactory::RollsCarFactory()
{
  printf("in %s\n", __func__);
}

RollsCarFactory::~RollsCarFactory()
{
  printf("in %s\n", __func__);
}

RollsCarBreak* RollsCarFactory::CreatCarBreak()
{
	return new RollsCarBreak;
}

RollsCarDoor* RollsCarFactory::CreatCarDoor()
{
	return new RollsCarDoor;
}


void TestFactoryPattern()
{
  auto fac1 = new FordCarFactory;
  CarBreak* myBreak1 = fac1->CreatCarBreak();
  CarDoor*  myDoor1 = fac1->CreatCarDoor();
  myBreak1->Draw();
  myDoor1->Draw();

  delete myBreak1;
  delete myDoor1;
  delete fac1;

  auto fac2 = new RollsCarFactory;
  CarBreak* myBreak2 = fac2->CreatCarBreak();
  CarDoor*  myDoor2 = fac2->CreatCarDoor();
  myBreak2->Draw();
  myDoor2->Draw();

  delete myBreak2;
  delete myDoor2;
  delete fac2;
}
