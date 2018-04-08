#include "stdafx.h"
#include "P03_New_Class_Features.h"
#include <memory>
#include <utility>      // std::forward
#include <string>
#include <vector>
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

    class Widget2 {
    public:
      // using std::forward to initialise member variables
      Widget2(std::string&& name, std::vector<int>&& coords)
        : m_name(std::forward<string>(name))
        , m_coordinates(std::forward<std::vector<int>>(coords))
      {
        printf("call Widget2 move ctor\n");
      }

    private:
      std::string m_name;
      std::vector<int> m_coordinates;
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

  void DemoForwarding()
  {
    FUNC_INFO;
    std::string name("triangle");
    std::vector<int> vec;
    ClassHierarchy::Widget2 g(std::move(name), std::move(vec));
  }

  namespace ClassDefault
  {
    class Widget {
    public:
      // Constructor initializer lists override defaults:
      Widget(int a) : x(a)
      {
        printf("x = %d\n", x);
      }

    private:
      // default initial values
      int x = 5;
      string name = "";

      // Uniform initialization syntax
      int y  { 6 };
      double wage { 0.0 };
    };

  }
  void DemoClassDefaultMemberFunctions()
  {
    /***************************************************************
    * The "special" member functions are implicity generated if used:
    * [1] Default constructor - Only if no user-declared constructors.
    * [2] Destructor
    * [3] Copy operations (copy constructor, copy operator=)
    *     Only if move operations not user-declared.
    * [4] Move operations (move constructor, move operator=)
    *     Only if copy operations not user-declared.
    ****************************************************************/
    FUNC_INFO;
    ClassDefault::Widget w {-1};
  }

  namespace InheritingConstructors
  {
    class Base {
    public:
      Base()
      {
        printf("call Base ctor\n");
      }
      
      virtual ~Base() {}

      explicit Base(int)
      {
        printf("call Base ctor Base(int)\n");
      }

      void f(int)
      {
        printf("call Base f(int)\n");
      }
    };

    class Derived : public Base {
    public:
      using Base::f;    // okay in C++98 and C++0x
      using Base::Base; // okay in C++0x only; causes implicit
                        // declaration of Derived::Derived(int),
                        // which, if used, calls Base::Base(int)
                        // overloads inherited Base::f
      void f()
      {
        printf("call Derived f()\n");
      }

      // overloads inherited Base ctor
      Derived(int x, int y)
      {
        printf("call Derived ctor Derived(int x, int y)\n");
      }
    };

    class A {
    public:
      explicit A(int x) {}
    };

    class B : public A {
    public:
      using A::A; // use base class constructor A::A(int)
    private:
      std::string name = "Uninitialized";
      int x = 0, y = 0;
    };
  }
  void DemoInheritingConstructors()
  {
    FUNC_INFO;
    InheritingConstructors::Derived d1(44); // okay in C++0x due to ctor inheritance
    d1.f(1);
    d1.f();
    InheritingConstructors::Derived d2(5, 10); // normal use of Derived::Derived(int, int)
    d1.f(2);
    d1.f();

    InheritingConstructors::B d(10);
  }
}