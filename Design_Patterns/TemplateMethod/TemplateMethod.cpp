#include "StdAfx.h"
#include "TemplateMethod.h"
namespace TemplateMethod {

  // Class EEGAlgorithm
  EEGAlgorithm::EEGAlgorithm()
  {
  }

  EEGAlgorithm::~EEGAlgorithm()
  {
  }

  void EEGAlgorithm::EEGDataProcess()
  {
    EEGDataRead();
    EEGFDCalculation();
    EEGDeviceClose();
  }

  void EEGAlgorithm::EEGDataRead()
  {
    cout << "Read Data from Device!" << endl;
  }

  void EEGAlgorithm::EEGFDCalculation()
  {
    cout << "EEGAlgorithm Method is used!" << endl;
  }

  void EEGAlgorithm::EEGDeviceClose()
  {
    cout << "The device is closed!" << endl;
  }

  // Class HiguchiAlgorithm

  HiguchiAlgorithm::HiguchiAlgorithm()
  {
  }

  HiguchiAlgorithm::~HiguchiAlgorithm()
  {
  }

  void HiguchiAlgorithm::EEGFDCalculation()
  {
    cout << "Higuchi Method is used!" << endl;
    //EEGAlgorithm::EEGFDCalculation();  // hook operation
  }

  // Class Boxcounting Method

  BoxcountingAlgorithm::BoxcountingAlgorithm()
  {
  }

  BoxcountingAlgorithm::~BoxcountingAlgorithm()
  {
  }

  void BoxcountingAlgorithm::EEGFDCalculation()
  {
    cout << "Box-counting Method is used!" << endl;
  }

  void TestTemplateMethod()
  {
    printf("------------------- in %s -------------------\n", __func__);
    HiguchiAlgorithm myMethod1;
    BoxcountingAlgorithm myMethod2;

    myMethod1.EEGDataProcess();
    myMethod2.EEGDataProcess();
  }
}