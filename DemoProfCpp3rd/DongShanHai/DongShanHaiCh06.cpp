#include "StdAfx.h"

#include <iostream>

#include "DongShanHai.h"

using namespace std;
namespace DemoClassMemberInitializationOrder 
{
  class Object
  {
  public:
    Object(int k) : // initialzation order is i, then j, regardless the order placed here
      j(k),         // j is initialised as 2
      i(j)          // i is initialised as random number before j (trap)
    {
    }

    void Print()
    {
      cout << "i " << i << ", j " << j << endl;
    }

  private:
    int i;
    int j;
  };

  void execute()
  {
    Object obj(2);
    obj.Print();
  }
}
void Ch06_DemoClassMemberInitializationOrder()
{
  FUNC_INFO;
  DemoClassMemberInitializationOrder::execute();
}

namespace DemoStaticClassMember
{
  class object
  {
  public:
    object(int a, int b, int c);
    void GetNumber() const;
    void GetSum() const;

  private:
    int A;
    int B;
    int C;
    int NUM;
    static int SUM;
  };

  int object::SUM = 0;

  object::object(int a, int b, int c)
  {
    A = a;
    B = b;
    C = c;
    NUM = A + B + C;
    SUM = A + B + C;
  }

  void object::GetNumber()const
  {
    cout << "Num=" << NUM << endl;;
  }

  void object::GetSum()const
  {
    cout << "Sum=" << SUM << endl;;
  }

  void execute()
  {
    object M(3, 7, 10);   // SUM = 3+7+10=20
    // M.GetSum(); // 20
    object N(14, 9, 11);  // SUM = 14+9+11=34
    M.GetNumber();        // NUM 3+7+10=20
    N.GetNumber();        // NUM 14+9+11=34
    M.GetSum(); // 34
    N.GetSum(); // 34
  }
}

void Ch06_DemoStaticClassMember()
{
  FUNC_INFO;
  DemoStaticClassMember::execute();
}

namespace DemoClassMemberInInitializationList
{
  class base 
  {
  public:
    base() { cout << "base constructor" << endl; }
    virtual ~base() { cout << "base destructor" << endl; }
  };
  class child : public base
  {
  public:
    child(int val);
    virtual ~child() { cout << "child destructor" << endl; }

  private:
    int& value;
    const double kPI;
  };

  child::child(int val) : value(val),   // reference variable
                          kPI(3.14159), // const variable
                          base()        // base class constructor
  {
    cout << "child ctor: value=" << value << " kPI=" << kPI << endl;
  }

  void execute()
  {
    child mychild(2);
  }
}

void Ch06_DemoClassMemberInInitializationList()
{
  FUNC_INFO;
  DemoClassMemberInInitializationList::execute();
}

namespace DemoStaticAndNonStaticMembers
{
  class object
  {
  public:
    static int i;
    int j;

    object(int a) : 
      // i(1), // 1 error: static member cannot be initialised inside class
      j(a)
    {
    }

    void func1() 
    {
      cout << i << j << endl;
    }
    static void func2()
    {
      // cannot use non-static member in static function,
      // j must be related to specified object
      // cout << i << j << endl;

      cout << i << endl;
    }
  };

  int object::i = -1; // static member is initialised outside class

  void execute()
  {
    object A(3);
  }
}

void Ch06_DemoStaticAndNonStaticMembers()
{
  FUNC_INFO;
  DemoStaticAndNonStaticMembers::execute();
}