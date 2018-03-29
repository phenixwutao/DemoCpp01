#pragma once
#include <string>

// Implementor
class DeviceImplement
{
public:
	DeviceImplement();
  virtual ~DeviceImplement();
  virtual void SwichOn();
	virtual void SwichOff();
};

class FridgeImplement : public DeviceImplement
{
public:
	FridgeImplement();
  virtual ~FridgeImplement();
  virtual void SwichOn();
	virtual void SwichOff();
};


class LampImplement : public DeviceImplement
{
public:
  LampImplement();
  virtual ~LampImplement();
  virtual void SwichOn();
	virtual void SwichOff();
};


// Abstraction
class Device
{
public:
	Device(const std::string& type);
	~Device();
	void SwichOn();
	void SwichOff();
private:
  std::string m_sTypeName;
	DeviceImplement* m_pImp = nullptr;
};

void TestBridge();