#pragma once
#include <iostream>
using namespace std;
namespace TemplateMethod {

  class EEGAlgorithm {
  public:
    EEGAlgorithm();
    virtual ~EEGAlgorithm();
    virtual void EEGDataProcess();			// Template Method
  protected:
    virtual void EEGDataRead();				// Primitive Method
    virtual void EEGFDCalculation();		// Primitive Method
    virtual void EEGDeviceClose();			// Primitive Method
  };


  class HiguchiAlgorithm : public EEGAlgorithm {
  public:
    HiguchiAlgorithm();
    virtual ~HiguchiAlgorithm();
  protected:
    virtual void EEGFDCalculation() override;
  };

  class BoxcountingAlgorithm : public EEGAlgorithm {
  public:
    BoxcountingAlgorithm();
    virtual ~BoxcountingAlgorithm();
  protected:
    virtual void EEGFDCalculation() override;
  };
  void TestTemplateMethod();
}