#include "stdafx.h"
#include "P02_New_Libs_Enhancement.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <forward_list>
#include <functional>
#include <regex>
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

  void DemoForwardList()
  {
    FUNC_INFO;
    forward_list<int> list;
    list.push_front(1);
    list.push_front(5);
    list.push_front(7);
    for (auto & it : list)
      cout << it << " ";
    cout << endl;

    list.pop_front();
    for (auto & it : list)
      cout << it << " ";
    cout << endl;

    list.clear();
    list.insert_after(list.before_begin(), 3);
    list.insert_after(list.begin(), 5);
    list.insert_after(list.begin(), 6);
    for (auto & it : list)
      cout << it << " ";
    cout << endl;
  }

  namespace MyRegExp
  {
    const std::regex SSNRegex(R"(\d{3}-\d{2}-\d{4})");
    bool looksLikeSSN(const std::string& text)
    {
      return std::regex_match(text, SSNRegex);
    }
    bool mayContainSSN(const std::string& text)
    {
      return std::regex_search(text, SSNRegex);
    }
    void dashifySSNs(std::string& text)
    {
      const std::string dashes("-----------");
      text = std::regex_replace(text, SSNRegex, dashes);
    }
  }
  void DemoRegularExpression()
  {
    FUNC_INFO;
    string text("modern.cpp.865-22-9866-X");
    auto fLike = MyRegExp::looksLikeSSN(text);
    printf("looks like SSN: %d\n", fLike);

    auto fHasSSN = MyRegExp::mayContainSSN(text);
    printf("contains   SSN: %d\n", fHasSSN);

    cout << text << endl;
    MyRegExp::dashifySSNs(text);
    cout << text << endl;
  }

  namespace CallableFunction {
    void myfunc(int a)
    {
      printf("call myfunc(%d)\n", a);
    }

    class Widget {
    public:
      using FuncPtr = void(*)(int);
      void operator()(int a) // function call operator
      {
        printf("call operator()(%d)\n", a);
      }
    };

    int someFunc(std::string&)
    {
      printf("call %s\n", __func__);
      return 1;
    }

    class Gadget {
    public:
      int operator()(std::string& str) // function call operator
      {
        printf("call %s\n", __func__);
        return std::stoi(str);
      }
    };
  }

  void DemoCallableEntity()
  {
    FUNC_INFO;
    void(*MyFuncPtr)(int) = CallableFunction::myfunc;
    MyFuncPtr(9);

    using FuncAlias = void(*)(int);
    FuncAlias func_alias = CallableFunction::myfunc;
    func_alias(3);

    CallableFunction::Widget w;
    w(2);
  }

  void DemoUsingStdFunction()
  {
    FUNC_INFO;
    std::function<int(std::string&)> f;
    f = CallableFunction::someFunc;
    string text("321");
    cout << f(std::ref(text)) << endl;

    f = [](std::string &s)->unsigned
    { s += "!"; return s.size(); };
    cout << f(text) << endl;

    CallableFunction::Gadget g;
    f = g;
    cout << f(text) << endl;
  }

  namespace BindBasis
  {
    int func(int x, int y)
    {
      printf("bind x %d y %d\n", x, y);
      return x + y;
    }
    class Widget {
    public:
      int calcSum(int x, int y)
      {
        printf("x= %d y= %d\n", x, y);
        return x + y;
      }
    };

    int funcParam(int a, int b, int c)
    {
      printf("a = %d, b = %d, c = %d\n", a,b,c);
      return a + b + c;
    }
  }
  void DemoBindBasis()
  {
    FUNC_INFO;
    // 1st argument is 10, 2nd argument is _1
    // std::placeholders max number of place holders is 20, starting from _1 ... _20
    auto bf = std::bind(BindBasis::func, 2, std::placeholders::_1);
    printf("call bf is: %d\n", bf(3));

    auto bf2 = std::bind(BindBasis::func, std::placeholders::_2, std::placeholders::_1);
    printf("call bf2 is: %d\n", bf2(2,3));
  }

  void DemoBindClassFunction()
  {
    FUNC_INFO;
    // bind class object
    BindBasis::Widget obj;
    auto funcBindObject = std::bind(&BindBasis::Widget::calcSum, obj, std::placeholders::_2, std::placeholders::_1);
    printf("bind Widget object: %d\n", funcBindObject(2, 3));

    // bind class object pointer
    BindBasis::Widget* pobj = new BindBasis::Widget;
    auto funcBindPtr = std::bind(&BindBasis::Widget::calcSum, pobj, std::placeholders::_2, std::placeholders::_1);
    printf("bind Widget object pointer: %d\n", funcBindPtr(4, 5));
    delete pobj;

    // bind class shared pointer
    std::shared_ptr<BindBasis::Widget> pWidShr = std::make_shared<BindBasis::Widget>();
    auto funcShared = std::bind(&BindBasis::Widget::calcSum, pWidShr, std::placeholders::_2, std::placeholders::_1);
    printf("bind Widget shared pointer: %d\n", funcShared(6, 7));

    // bind class unqiue pointer
    std::unique_ptr<BindBasis::Widget> pWidUniq = std::make_unique<BindBasis::Widget>();
    // std::unique_ptr must be wrapped by std::ref when bound, because std::unique_ptr isn't
    // copyable. It's only movable.
    auto funcUniq = std::bind(&BindBasis::Widget::calcSum, std::ref(pWidUniq), std::placeholders::_2, std::placeholders::_1);
    printf("bind Widget unqiue pointer: %d\n", funcUniq(8, 9));

    // Binding Beyond the 2nd Argument
    std::vector<BindBasis::Widget> vec;
    for (int i = 0; i < 5; i++)
    {
      BindBasis::Widget wid;
      vec.emplace_back(wid);
    }

    for_each(vec.begin(), vec.end(),
      std::bind(&BindBasis::Widget::calcSum, std::placeholders::_1, 10, 20));
  }

  void DemoBindPositions()
  {
    FUNC_INFO;
    using namespace std::placeholders;
    std::function<int(int, int)> f1 = std::bind(BindBasis::funcParam, _1, _1, _2);
    int x(1), y(2), z(3);
    printf("f1 %d\n", f1(x, y));

    std::function<int(int, int, int)> f2 = std::bind(BindBasis::funcParam, _3, _2, _1);
    printf("f2 %d\n", f2(x, y, z));

    // use lambda, the same as std::bind
    auto f3 = [=](int x, int y, int z) -> int
    {
      return BindBasis::funcParam(z, y, x);
    };
    printf("f3 %d\n", f3(x, y, z));
  }
}
