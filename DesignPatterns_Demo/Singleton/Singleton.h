#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H

namespace DemoSingletonPattern {
  class Singleton
  {
  public:
    static Singleton* GetInstancePtr();
    static Singleton  GetInstance();
    static void Destroy(Singleton*);
    void Test();

  private:
    Singleton() {}
    ~Singleton() {}
    static Singleton* m_pStatic;
  };

  void TestSingletonPattern();
}
#endif