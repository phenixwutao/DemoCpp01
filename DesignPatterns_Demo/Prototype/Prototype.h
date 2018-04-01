#pragma once
#ifndef PROTOTYPE_H
#define PROTOTYPE_H

namespace DemoPrototypePattern {
  // Prototype Pattern also called clone pattern
  class Prototype
  {
  public:
    Prototype() {}
    virtual ~Prototype() {}

    virtual Prototype* Clone() = 0;
  };

  class ConcreatePrototype1 : public Prototype
  {
  public:
    ConcreatePrototype1();
    ConcreatePrototype1(const ConcreatePrototype1&);
    virtual ~ConcreatePrototype1();

    virtual Prototype* Clone();
  };

  class ConcreatePrototype2 : public Prototype
  {
  public:
    ConcreatePrototype2();
    ConcreatePrototype2(const ConcreatePrototype2&);
    virtual ~ConcreatePrototype2();

    virtual Prototype* Clone();
  };

  void TestPrototypePattern();
}
#endif
