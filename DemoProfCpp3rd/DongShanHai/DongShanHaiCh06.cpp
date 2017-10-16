#include "StdAfx.h"

#include <iostream>

#include "DongShanHai.h"

using namespace std;
namespace DemoClassMemberInitializationOrder 
{
  class Object
  {
  public:
    Object(int k) : // initialzation order is i, then j
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
