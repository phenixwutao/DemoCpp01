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
      virtual ~Base() = default;
      virtual void info()
      {
        printf("Base info\n");
      }

      void Run() {
        printf("Base run\n");
      }
    };

    class Sub : public Base
    {
    public:
      virtual ~Sub() = default;

      void info() override
      {
        printf("Sub info\n");
      }

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

  void chap10DemoClassMethodOverride()
  {
    FUNC_INFO;
    DemoOverload::Base b;
    b.info();
    DemoOverload::Sub s;
    s.info();

    DemoOverload::Base& refb = b;
    refb.info();

    DemoOverload::Base& refs = s;
    refs.info();

    DemoOverload::Base* pb = new DemoOverload::Base;
    pb->info();
    delete pb;

    DemoOverload::Base* ps = new DemoOverload::Sub;
    ps->info();
    delete ps;
  }
}