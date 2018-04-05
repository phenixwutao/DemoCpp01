#include "stdafx.h"
#include "P02_New_Libs_Enhancement.h"

#include <memory>
using namespace std;

namespace NewLibsEnhancement {

  namespace UniquePointer {
    class Base
    {
    public:
      virtual ~Base()
      {
        printf("call %s\n", __func__);
      }

      virtual void work()
      {
        printf("call Base %s\n", __func__);
      }
    };
    class Derived : public Base
    {
    public:
      virtual ~Derived()
      {
        printf("call %s\n", __func__);
      }

      void work() override
      {
        printf("call Derived %s\n", __func__);
      }
    };
  };
  void DemoUniquePointer()
  {
    FUNC_INFO;
    std::unique_ptr<UniquePointer::Derived> pd(new UniquePointer::Derived);
    // std::unique_ptr<UniquePointer::Base> pb(pd); // error, cannot copy
    std::unique_ptr<UniquePointer::Base> pb(std::move(pd)); // OK, move
    pb->work();
  }
}
