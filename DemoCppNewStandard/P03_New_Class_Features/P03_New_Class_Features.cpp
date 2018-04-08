#include "stdafx.h"
#include "P03_New_Class_Features.h"
#include <memory>
using namespace std;

namespace NewClassFeatures {
  namespace DemoMove
  {
    class Widget {
    public:
      // constructor
      Widget()
      {
        printf("call %s constructor\n", __func__);
      }

      // copy constructor
      Widget(const Widget&)
      {
        printf("call %s copy constructor\n", __func__);
      }

      // move constuctor
      Widget(Widget&&)
      {
        printf("call %s move constuctor\n", __func__);
      }

      // copy assignment op
      Widget& operator=(const Widget&)
      {
        printf("call %s copy assignment\n", __func__);
        return *this;
      }

      // move assignment op
      Widget& operator=(Widget&&)
      {
        printf("call %s move assignment\n", __func__);
        return *this;
      }

      ~Widget()
      {
        printf("call %s destructor\n", __func__);
      }
    };
    Widget createWidget()
    {
      Widget wid;
      return wid;
    }
  }
  void DemoCopyMoveObject()
  {
    FUNC_INFO;
    {
      printf("test 1\n");
      auto wid = DemoMove::createWidget(); // factory function
    }

    {
      printf("test 2\n");
      DemoMove::Widget w1;
      DemoMove::Widget w2 = w1;       // lvalue src --> copy req’d
      w2 = DemoMove::createWidget();  // rvalue src --> move okay
      w1 = w2;  // lvalue src --> copy required
    }
  }

  namespace ClassHierarchy
  {
    class Widget {
    public:
      Widget()
      {
        printf("call Widget ctor\n");
      }

      Widget(const Widget&)
      {
        printf("call Widget copy ctor\n");
      }

      //Widget(Widget&&) 
      //{
      //  printf("call Widget move ctor\n");
      //}
    };

    class Gadget {
    public:
      Gadget()
      {
        printf("call Gadget ctor\n");
      }
      Gadget(Gadget&& rhs) // move ctor
        : w(std::move(rhs.w)) // request to move w’s value
      {
        printf("call Gadget move ctor\n");
      }
    private:
      Widget w; // lacks move support
    };
  }
  void DemoMoveClassHierarchy()
  {
    FUNC_INFO;
    ClassHierarchy::Gadget g;

    // it calls Gadget move ctor, but calls Widget copy ctor
    // because Widget move ctor is not supplied. If move ctor is supplied, will be used.
    ClassHierarchy::Gadget g2 = std::move(g);
  }
}