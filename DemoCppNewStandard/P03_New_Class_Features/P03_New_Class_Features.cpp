#include "stdafx.h"
#include "P03_New_Class_Features.h"
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
}