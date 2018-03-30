#pragma once
namespace FacadePattern {

  // Parts of the car
  // Class Door
  class Door {
  public:
    Door();
    virtual ~Door();
    virtual void Open();
    virtual void Close();
  };

  // Class Engine
  class Engine {
  public:
    Engine();
    virtual ~Engine();
    virtual void Start();
    virtual void Stop();
  };

  // Class Break
  class Brake {
  public:
    Brake();
    virtual ~Brake();
    virtual void Skid();
  };

  // Class GPS
  class GPS {
  public:
    GPS();
    virtual ~GPS();
    virtual void Open();
    virtual void TurnOff();
    virtual void GetPosition();
    virtual void DisplayPosition();

  private:
    double longitude;
    double latitude;
  };

  // Facade class
  class Car {
  public:
    Car();
    virtual ~Car();
    virtual void OpenDoor();
    virtual void LockDoor();
    virtual void Start();
    virtual void Skid();
    virtual void Stop();
    virtual void DisplayPosition();
  private:
    Door*   myDoor;
    Engine* myEngine;
    GPS*    myGPS;
    Brake*  myBrake;
  };
  void TestFacadePattern();
}