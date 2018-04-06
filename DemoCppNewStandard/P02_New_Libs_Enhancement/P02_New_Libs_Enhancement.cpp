#include "stdafx.h"
#include "P02_New_Libs_Enhancement.h"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
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

    class DemoObject {
    public:
      DemoObject(int i) : m_wCount(i)
      {
        printf("DemoObject constructor %d\n", m_wCount);
      }

      ~DemoObject()
      {
        printf("DemoObject destructor %d\n", m_wCount);
      }

      DemoObject(const DemoObject& lhs)
      {
        printf("DemoObject copy constructor this: %d  %d\n",this->m_wCount, lhs.m_wCount);
      }

      DemoObject(DemoObject&& lhs)
      {
        printf("DemoObject move constructor this: %d  %d\n", this->m_wCount, lhs.m_wCount);
      }

      DemoObject& operator=(const DemoObject& lhs)
      {
        printf("DemoObject copy assignment constructor this: %d  %d\n", this->m_wCount, lhs.m_wCount);
      }

      DemoObject& operator=(DemoObject&& lhs)
      {
        printf("DemoObject move assignment constructor this: %d  %d\n", this->m_wCount, lhs.m_wCount);
      }

      const int GetCount() const
      {
        return m_wCount;
      }

    private:
      int m_wCount = 0;
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

  void DemoUniquePointerMoveObject()
  {
    FUNC_INFO;
    const int kMAX = 6;
    // Inserts a new element at the end of the vector,
    // right after its current last element.
    printf("using emplace_back ===================\n");
    {
      std::vector<std::unique_ptr<UniquePointer::DemoObject>> vec;
      for (int i = 1; i <= kMAX; ++i)
      {
        vec.emplace_back(std::make_unique<UniquePointer::DemoObject>(i));
      }
    }

    printf("using push_back ===================\n");
    {
      std::vector<UniquePointer::DemoObject> vec2;
      for (int i = 1; i <= kMAX; ++i)
      {
        UniquePointer::DemoObject obj(i);
        vec2.push_back(obj);
      }
    }

    printf("using push_back std::ref ===================\n");
    {
      std::vector<UniquePointer::DemoObject> vec3;
      for (int i = 1; i <= kMAX; ++i)
      {
        UniquePointer::DemoObject obj(i);
        vec3.push_back(std::ref(obj));
      }
    }


    printf("using push_back std::move ===================\n");
    {
      std::vector<UniquePointer::DemoObject> vec4;
      for (int i = 1; i <= kMAX; ++i)
      {
        UniquePointer::DemoObject obj(i);
        vec4.push_back(std::move(obj));
      }
      printf("About to clear\n");
      vec4.clear();
      vec4.emplace_back(UniquePointer::DemoObject(1));
      vec4.emplace_back(UniquePointer::DemoObject(3));
      vec4.emplace_back(UniquePointer::DemoObject(9));
      vec4.emplace_back(UniquePointer::DemoObject(7));
      vec4.emplace_back(UniquePointer::DemoObject(4));
      vec4.emplace_back(UniquePointer::DemoObject(2));

      //std::sort(vec4.begin(), vec4.end(),
      //  [=](const UniquePointer::DemoObject& p1, const UniquePointer::DemoObject& p2) 
      //  {
      //  p1.GetCount() < p2.GetCount();
      //  });
    }

  }
}
