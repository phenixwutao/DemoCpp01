#include "StdAfx.h"

#include "Bridge.h"
#include <iostream>
using namespace std;

// DeviceImplement
DeviceImplement::DeviceImplement()
{
  printf("in %s\n", __func__);
}

DeviceImplement::~DeviceImplement()
{
  printf("in %s\n", __func__);
}

void DeviceImplement::SwichOn()
{
	cout<<"General Electric Device: On!"<<endl;
}

void DeviceImplement::SwichOff()
{
	cout<<"General Electric Device: Off!"<<endl;
}

// FridgeImplement
FridgeImplement::FridgeImplement()
{
  printf("in %s\n", __func__);
}

FridgeImplement::~FridgeImplement()
{
  printf("in %s\n", __func__);
}

void FridgeImplement::SwichOn()
{
	cout<<"Fridge: On!"<<endl;
}

void FridgeImplement::SwichOff()
{
	cout<<"Fridge: Off!"<<endl;
}

// LampImplement
LampImplement::LampImplement()
{
  printf("in %s\n", __func__);
}

LampImplement::~LampImplement()
{
  printf("in %s\n", __func__);
}

void LampImplement::SwichOn()
{
	cout<<"Lamp: On!"<<endl;
}

void LampImplement::SwichOff()
{
	cout<<"Lamp: Off!"<<endl;
}

// Device
Device::Device(const std::string& type)
{
  m_sTypeName = type;
  if (m_sTypeName == "fridge")
  {
    m_pImp = new FridgeImplement();
  }
  else if (m_sTypeName == "lamp")
  {
    m_pImp = new LampImplement();
  }
  else {
    m_pImp = new DeviceImplement();
  }
}

Device::~Device()
{
  delete m_pImp;
}

void Device::SwichOn()
{
  m_pImp->SwichOn();
}

void Device::SwichOff()
{
  m_pImp->SwichOff();
}

void TestBridge()
{
  printf("in %s\n", __func__);
  Device* myDevices[3];
  myDevices[0] = new Device("fridge");
  myDevices[1] = new Device("lamp");
  myDevices[2] = new Device("other type");
  myDevices[0]->SwichOn();
  myDevices[1]->SwichOn();
  myDevices[2]->SwichOn();
  myDevices[0]->SwichOff();
  myDevices[1]->SwichOff();
  myDevices[2]->SwichOff();
  for (auto item : myDevices)
  {
    delete item;
  }
}
