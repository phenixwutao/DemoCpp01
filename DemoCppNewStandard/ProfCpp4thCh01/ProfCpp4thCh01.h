#pragma once
#ifndef PROFCPP4THCH01_H
#define PROFCPP4THCH01_H
namespace chap01
{
  // nested namespaces require compiler flag '/std:c++17'
  namespace MyLib::MyMath::General
  {
    int add(int a, int b);
  }
  void ch01Typetest();
  void ch01DemoNamespaceCpp17();
  void ch01DemoEnumClass();
  void ch01DemoSwitchFallthrough();
  void ch01DemoFunctionReturnTypeDeduction();
  void ch01DemoArrayInitializationSize();
  void ch01DemoStdArray();
  void ch01DemoStructuredBindings();
}
#endif
