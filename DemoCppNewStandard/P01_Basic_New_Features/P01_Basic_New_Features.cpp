#include "stdafx.h"
#include "P01_Basic_New_Features.h"

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <regex>
#include <algorithm>
#include <thread>
#include <future>
using namespace std;

namespace BasicNewFeatures {
  void DemoBasicForLoop()
  {
    FUNC_INFO;
    vector<int> vec;
    for (int i = 1; i <= 10; ++i)
    {
      vec.emplace_back(i);
    }

    for (auto& it : vec)
    {
      cout << it << "\t";
    }
    cout << endl;

    for (volatile auto& it : vec)
    {
      it += 3;
      cout << it << "\t";
    }
    cout << endl;

    DEMO_INFO("ranged based for loop on array");
    short employee[10]{1};
    for (auto& it : employee)
    {
      cout << it << "\t";
    }
    cout << endl;
  }
  namespace {
    void CheckPointer(int* pVal)
    {
      printf("calling %s(int* pVal)\n", __func__);
    }
    void CheckPointer(int Val)
    {
      printf("calling %s(int Val)\n", __func__);
    }
    void CheckNullPointer(int* pVal)
    {
      printf("calling %s(int* pVal)\n", __func__);
    }
  }
  void DemoNullptr()
  {
    FUNC_INFO;
    CheckPointer(nullptr);
    CheckPointer(0);
    CheckPointer(NULL);
  }
  
  template<typename F, typename P>
  void logAndCall(F func, P param)
  {
    func(param);
  }

  void DemoTemplateFunctionNullptr()
  {
    // logAndCall(CheckNullPointer, 0); // error
    // logAndCall(CheckNullPointer, NULL); // error
    logAndCall(CheckNullPointer, nullptr); // ok
  }
  void DemoUnicodeSupport()
  {
    FUNC_INFO;
    std::string   s1("hello");     // std::basic_string<char>
    std::wstring  s2(L"hello");    // std::basic_string<wchar_t>
    std::u16string s3(u"hello");   // std::basic_string<char16_t>
    std::u32string s4(U"hello");   // std::basic_string<char32_t>
  }

  void DemoRawString()
  {
    std::string noNewlines(R"(\n\n)");
    std::string cmd(R"(ls /home/docs | grep ".pdf")");
    std::string withNewlines(R"(Line 1 of the string...
                                Line 2 C:\IT2\8.5\SCM ...
                                Line 3)");
    cout << noNewlines << endl;
    cout << cmd << endl;
    cout << withNewlines << endl;

    auto s1 = LR"(Raw Wide string literal \t (without a tab))";
    auto s2 = u8R"(Raw UTF-8 string literal \n (without a newline))";
    auto s3 = uR"(Raw UTF-16 string literal \\ (with two backslashes))";
    auto s4 = UR"(Raw UTF-32 string literal \u2620 (without a code point))";

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;

    // Raw text delimiters may be customized:
    // R"!(        )!"
    // R"xyzzy(    )xyzzy"
    std::regex re1(R"!("operator\(\)"|"operator->")!"); // "operator()"|
                                                        // "operator->"
    std::regex re2(R"xyzzy("\([A-Za-z_]\w*\)")xyzzy"); // "(identifier)"
    auto name = R"HHH(test folder C:\Program files\IT2 Solutions\AppServer;)HHH";
    cout << name << endl;
  }
  namespace UniformInitialization
  {
    struct Point
    {
      Point(int x, int y)
      {
      }

      int x;
      int y;
    };

    struct Point1
    {
      int x;
      int y;
    };

    class Point2
    {
    public:
      Point2(int a, int b)
      {
      }
    private:
      int x;
      int y;
    };

    class Widget {
    public:
      Widget() : data{ 1, 2, 3, 4, 5 } {}
    private:
      const int data[5];
    };
    
    void funcUniformInitialization(const std::vector<int>& v) // func. declaration
    {
    }

    Point2 makePoint()  // return expression;
                        // calls Point2 ctor
    {
      return { 0, 0 };
    }

    class Wid2 {
    public:
      explicit Wid2(int a) {}
    private:
      int x;
    };
  }
  void DemoUniformInitializationSyntax()
  {
    int z { 3 };
    int zID[] = {1,2,3};
    UniformInitialization::Point t1{ 1,2 };
    UniformInitialization::Point t2(3, 4);
    const UniformInitialization::Point t3 = { 2,3 };


    const int val1 { 5 };
    const int val2 { 5 };
    int a[] { 1, 2, val1, val1 + val2 };
    const UniformInitialization::Point1 p1{ 10, 20 }; // Uniform Initialization
    const UniformInitialization::Point2 p2{ 10, 20 }; // calls Point2 ctor
    const std::vector<int> cv{ a[0], 20, val2 };
    const float * pData = new const float[4]{ 1.5, val1 - val2, 3.5, 4.5 };
    delete pData;
    
    auto p3 = UniformInitialization::makePoint();

    UniformInitialization::funcUniformInitialization({ val1, val2, 10, 20, 30 }); // function argument

    UniformInitialization::Wid2 w1 { 10 };
    UniformInitialization::Wid2 w2 (10);
    // UniformInitialization::Wid2 w3 = { 10 };// error
    // UniformInitialization::Wid2 w4 = (10);  // error
    UniformInitialization::Wid2 w5 (10.5);   // compiler warning
    // UniformInitialization::Wid2 w6 { 10.5 }; // compiler error
  }

  namespace InitializerLists
  {
    class Widget3 {
    public:
      Widget3(double value, double uncertainty)      // #1
      {
        cout << "Widget3 call #1" << endl;
      }

      Widget3(std::initializer_list<double> values)  // #2
      {
        cout << "Widget3 call #2 double" << endl;
      }
      Widget3(std::initializer_list<int> values)  // #3
      {
        cout << "Widget3 call #3 int" << endl;
      }
      Widget3(std::initializer_list<string> values)  // #4
      {
        cout << "Widget3 call #4 string" << endl;
      }
    };
  }
  void DemoInitializerLists()
  {
    double d1(1.1), d2(2.2);
    InitializerLists::Widget3 w2 (d1, d2);   // calls #1
    InitializerLists::Widget3 w1 { d1, d2 }; // calls #2
    InitializerLists::Widget3 w3 { 1, 2, 3};
    InitializerLists::Widget3 w4 { 1.0f,2.0,3.0 };
    InitializerLists::Widget3 w5 {"hello","world","miss"};
  }

  void DemoLambdaFunctions()
  {
    FUNC_INFO;
    std::vector<int> vec;
    vec.emplace_back(1);
    vec.emplace_back(10);
    vec.emplace_back(3);
    vec.emplace_back(8);
    vec.emplace_back(6);
    vec.emplace_back(2);
    auto vecPredict = [](const int& v1, const int& v2)
    {
      return v1 < v2; 
    };

    std::sort(vec.begin(), vec.end(), vecPredict);
    for (const auto& it : vec)
      cout << it << endl;

    // capture local variables by copy
    int wMin = 4;
    int wMax = 9;
    auto it = std::find_if(vec.begin(), vec.end(),
      [wMin, wMax](int i) {return i > wMin && i < wMax; });
    cout << *it << endl;

    // capture local variables by reference
    auto it2 = std::find_if(vec.cbegin(), vec.cend(),
      [&wMin, &wMax](int i) {return i > wMin && i < wMax; });
    cout << *it2 << endl;

    // capture local variables by copy and reference
    it2 = std::find_if(vec.cbegin(), vec.cend(),
      [wMin, &wMax](int i) {return i > wMin && i < wMax; });
    cout << *it2 << endl;

    // capture mode default by copy
    it2 = std::find_if(vec.cbegin(), vec.cend(),
      [=](int i) {return i > wMin && i < wMax; });
    cout << *it2 << endl;

    // capture mode default by reference
    it2 = std::find_if(vec.cbegin(), vec.cend(),
      [&](int i) {return i > wMin && i < wMax; });
    cout << *it2 << endl;

    // Default overridable on a per-variable basis
    // default is captured by value, but wMax is by reference
    it2 = std::find_if(vec.cbegin(), vec.cend(),
      [=,&wMax](int i) {return i > wMin && i < wMax; });
    cout << *it2 << endl;
  }

  namespace DemoLambda {
    class MyLambda
    {
    public:
      void operation();
    private:
      vector<int> list;
      int wMin = 4;
    };

    void MyLambda::operation()
    {
      list.emplace_back(1);
      list.emplace_back(3);
      list.emplace_back(5);
      list.emplace_back(8);

      // capture class member by this pointer
      auto it = std::find_if(list.begin(), list.end(),
        [this](int i) {return i > wMin; });
      cout << *it << endl;

      // default capture mode (by copy) makes this available:
      it = std::find_if(list.begin(), list.end(),
        [=](int i) {return i > wMin; });
      cout << *it << endl;

      // default capture mode (by reference) makes this available:
      it = std::find_if(list.begin(), list.end(),
        [&](int i) {return i > wMin; });
      cout << *it << endl;
    }
  }
  void DemoLambdaCapturingClassMembers()
  {
    FUNC_INFO;
    DemoLambda::MyLambda lamb;
    lamb.operation();
  }
  
  void DemoLambdaReturnTypes()
  {
    FUNC_INFO;
    vector<double> vec;
    vec.emplace_back(1.1);
    vec.emplace_back(1.2);
    vec.emplace_back(1.3);
    std::transform(vec.begin(), vec.end(), vec.begin(),
      [](double val)->double
      {return val * val; });

    for (const auto& it : vec)
      cout << it << endl;

    // Trailing Return Type
    auto mySquare = [=](int i)->int {return i * i; };
    cout << mySquare(3) << endl;
  }

  namespace LambdaParameter
  {
    void DoWork()
    {
      auto trd_id = std::this_thread::get_id();
      cout << "running " << __func__ << " in thread " << trd_id << endl;
    }
  }
  void DemoLambdaWithoutParameterLists()
  {
    FUNC_INFO;
    // lambda with empty parameter list
    thread t1( []() { LambdaParameter::DoWork(); } );
    t1.join();

    // lambda without empty parameter list
    thread t2( [] { LambdaParameter::DoWork(); });
    t2.join();
  }

  namespace StoringClosures
  {
    void UseFunction(std::function<bool(long)> func, long val)
    {
      printf("---- in %s  %d\n", __func__, func(val));
    }

    // Storing Closures for class data members
    class Widget {
    private:
      std::function<bool(long)> eventHandler; // fine
    };
  }
  void DemoLambdaStoringClosures()
  {
    FUNC_INFO;
    long val = 6;
    // using auto
    auto func1 = [=](long x) { return x % 5 == 0; };
    cout << (func1(val) == true ? "Yes" : "No")<< endl;

    // using std::function< return-type (parameter) >
    // function type is std::function<bool(long)>
    val = 10;
    std::function<bool(long)> func2 = [=](long x) { return x % 5 == 0; };
    cout << (func2(val) == true ? "Yes" : "No") << endl;

    // function type is std::function<auto (long)->bool>
    std::function<auto(long)->bool> func3 = [=](long x) { return x % 5 == 0; };
    cout << (func3(val) == true ? "Yes" : "No") << endl;

    StoringClosures::UseFunction(func3, val);
  }

  void DemoLambdasAsContainerComparisonFunctions()
  {
    FUNC_INFO;
    auto cmpFunction = [](int a, int b) // compare values, not pointer
                       { return a > b; };
    // setup sort function (default is less than)
    std::set<int, decltype(cmpFunction)> s(cmpFunction); // sort set that way
    s.insert(9);
    s.insert(3);
    s.insert(6);
    s.insert(4);
    for (const auto& it : s)
      cout << it << " ";
    cout << endl;
  }

  namespace DemoUsing {
    void func(int a)
    {
      printf("call func %d\n", a);
    }
  }
  void DemoUsingVersusTypedef()
  {
    FUNC_INFO;
    typedef void(*CallBackPtr1)(int); // function pointer typedef
    CallBackPtr1 myCallBack1 = &DemoUsing::func;
    myCallBack1(1);

    using CallBackPtr2 = void(*)(int); // by using
    CallBackPtr2 myCallBack2 = DemoUsing::func;
    myCallBack2(2);
  }

  namespace BasicThread
  {
    void doThis()
    {
      printf("call %s\n", __func__);
    }

    class Widget {
    public:
      void operator()() const
      {
        printf("call %s\n", __func__);
      }

      void normalize(long double, int, const std::vector<float>&)
      {
        printf("call %s\n", __func__);
      }
    };
  }

  void DemoBasicThreads()
  {
    FUNC_INFO;
    std::thread t1(BasicThread::doThis); // run function asynch as normal
    t1.join();

    BasicThread::Widget w;
    std::thread t2(w); // "run" class function object asynch.
    t2.join();

    long double ld = 100.0;
    int x =2;
    vector<float> vec { 1.0F, 2.0F, 3.0F };
    // "run" closure asynch (lambda expression function)
    std::thread t3( [&](){ w.normalize(ld, x, vec); } );
    t3.join();
  }

  namespace BasicThreadLifetime
  {
    void f1(int& xParam, int& yParam)
    {
      xParam = 1;
      yParam = 2;
      printf("call %s  %d  %d\n", __func__, xParam, yParam);
    }

    void f2(int xParam, int yParam)
    {
      printf("call %s  %d  %d\n", __func__, xParam, yParam);
    }
    void f3(int xVal, const BasicThread::Widget& wVal)
    {}
    void f4(const int& xParam, const int& yParam)
    {
      printf("call %s  %d  %d\n", __func__, xParam, yParam);
    }
  }
  void DemoBasicThreadLifetime()
  {
    FUNC_INFO;
    int xParam(3), yParam(4);
    printf("1 call %s  %d  %d\n", __func__, xParam, yParam);

    std::thread t1(BasicThreadLifetime::f1, std::ref(xParam), std::ref(yParam));
    printf("2 call %s  %d  %d\n", __func__, xParam, yParam);

    t1.join();
    printf("3 call %s  %d  %d\n", __func__, xParam, yParam);

    // okay, closure holds a copy
    std::thread t2([=] { BasicThreadLifetime::f2(xParam, yParam); });
    t2.join();

    // okay, closure holds a reference
    std::thread t3([&] { BasicThreadLifetime::f2(xParam, yParam); });
    t3.join();

    // okay, closure holds a reference
    std::thread t4([&] { BasicThreadLifetime::f1(xParam, yParam); });
    t4.join();

    // error, closure holds a copy
    // std::thread t5([=] { BasicThreadLifetime::f1(xParam, yParam); });

    // invoke f3 with copies
    int xx = 9;
    BasicThread::Widget wVal;
    std::thread t6(std::bind(BasicThreadLifetime::f3, xx, wVal));
    t6.join();

    xParam = 7;
    yParam = 8;
    std::thread t7(BasicThreadLifetime::f4, xParam, yParam);
    t7.join();
  }

  namespace ThreadAsynchronousCall {
    int bestValue(int x, int y)
    {
      return x < y ? y : x;
    }
  }
  void DemoThreadAsynchronousCall()
  {
    FUNC_INFO;
    std::future<int> func = std::async([]() {return ThreadAsynchronousCall::bestValue(10, 13); });
    // get result or exception:
    auto wOutput = func.get();
    cout << "future output is " << wOutput << endl;


    // using std::launch::async function runs on a new thread
    std::future<int> funcAsynch = std::async(std::launch::async, []() {return ThreadAsynchronousCall::bestValue(10, 13); });
    wOutput = funcAsynch.get();
    cout << "async output is " << wOutput << endl;

    // using std::launch::deferred function runs on calling thread
    std::future<int> funcDeferred = std::async(std::launch::deferred, []() {return ThreadAsynchronousCall::bestValue(10, 13); });
    wOutput = funcDeferred.get();
    cout << "deferred output is " << wOutput << endl;

    // using Automatic: The function chooses the policy automatically (at some point).
    // This depends on the system and library implementation, which generally optimizes for
    // the current availability of concurrency in the system.
    std::future<int> funcAutomatic = std::async(launch::async | launch::deferred, []() {return ThreadAsynchronousCall::bestValue(10, 13); });
    wOutput = funcAutomatic.get();
    cout << "Automatic output is " << wOutput << endl;
  }

}