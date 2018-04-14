#include "stdafx.h"
#include "ProfCpp4thCh10.h"

#include <iostream>
using namespace std;

namespace chap10
{
  namespace DemoOverload
  {
    class Base
    {
    public:
      void Run() {
        printf("Base run\n");
      }
    };

    class Sub : public Base
    {
    public:
      void Run() {
        printf("Sub run\n");
      }
    };
  }

  void chap10DemoClassMethodOverload()
  {
    FUNC_INFO;
    DemoOverload::Base b;
    b.Run();
    DemoOverload::Sub s;
    s.Run();

    DemoOverload::Base& refb = b;
    refb.Run();

    DemoOverload::Base& refs = s;
    refs.Run();

    DemoOverload::Base* pb = new DemoOverload::Base;
    pb->Run();
    delete pb;

    DemoOverload::Base* ps = new DemoOverload::Sub;
    ps->Run();
    delete ps;
  }
}