#include "stdafx.h"
#include "ProfCpp4thCh10.h"
#include "SpreadsheetCell10.h"
#include "DoubleSpreadsheetCell10.h"
#include "StringSpreadsheetCell10.h"

#include <iostream>
#include <vector>
#include <memory>
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
      virtual void calc() final {}
    };

    class Sub : public Base
    {
    public:
      virtual ~Sub() = default;

      void info() override
      {
        printf("Sub info\n");
      }
      
      // void calc() override {} // cannot override this function

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

  namespace VirtualMethod
  {
    class Base {
    public:
      Base()
      {
        info();
      }
      virtual ~Base() = default;
      virtual void info() {  printf("Base info\n");  }
    };

    class Sub : public Base {
    public:
      Sub()
      {
        info();
      }
      virtual ~Sub() = default;
      virtual void info() { printf("Sub info\n"); }
    };

    class Object
    {
    public:
      Object() { cout << "2\n"; }
      virtual ~Object() { cout << "2\n"; }
    };

    class Parent
    {
    public:
      Parent() { cout << "1\n"; }
      virtual ~Parent() { cout << "1\n"; info(); }
      virtual void info() { cout << "Parent info" << endl; }
    };

    class Child : public Parent
    {
    public:
      Child() { cout << "3\n"; }
      virtual ~Child() { cout << "3\n"; info(); }
      virtual void info()
      {
        // Microsoft Visual C++ supports the __super keyword
        __super::info();

        cout << "Child info" << endl;
      }

    private:
      Object mObj;
    };
  }
  void chap10DemoConstructorCallVirtualMethod()
  {
    FUNC_INFO;
    VirtualMethod::Base* p = new VirtualMethod::Sub;
    delete p;

    VirtualMethod::Parent* pParent = new VirtualMethod::Child;
    delete pParent;
  }

  namespace PolymorphicSpreadsheet
  {
    StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs,
                                    const StringSpreadsheetCell& rhs)
    {
      StringSpreadsheetCell newCell;
      newCell.set(lhs.getString() + rhs.getString());
      return newCell;
    }
  }

  void chap10DemoPolymorphicSpreadsheet()
  {
    FUNC_INFO;
    vector<unique_ptr<SpreadsheetCell>> cellArray;

    cellArray.push_back(make_unique<StringSpreadsheetCell>());
    cellArray.push_back(make_unique<StringSpreadsheetCell>());
    cellArray.push_back(make_unique<DoubleSpreadsheetCell>());

    cellArray[0]->set("hello");
    cellArray[1]->set("10");
    cellArray[2]->set("18");

    cout << "Vector values are [" << 
      cellArray[0]->getString() << "," <<
      cellArray[1]->getString() << "," <<
      cellArray[2]->getString() << "]" << endl;

    DoubleSpreadsheetCell myDbl;
    myDbl.set(8.4);

    using namespace PolymorphicSpreadsheet;
    // call copy constructor from DoubleSpreadsheetCell, then call operator+
    StringSpreadsheetCell result = myDbl + myDbl;
    cout << endl << result.getString() << endl;

    // explicitly call PolymorphicSpreadsheet::operator+
    auto result2 = PolymorphicSpreadsheet::operator+(myDbl, myDbl);
    cout << result2.getString() << endl;
  }

}