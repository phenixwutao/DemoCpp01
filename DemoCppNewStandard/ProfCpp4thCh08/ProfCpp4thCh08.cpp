#include "stdafx.h"
#include "ProfCpp4thCh08.h"
#include "SpreadsheetCell08.h"

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <string>
#include <cassert>
#include <utility>
#include <type_traits>

using namespace std;
namespace chap08
{
  namespace InitializerListCtor 
  {
    class EvenSequence
    {
    public:
      EvenSequence(initializer_list<double> args)
      {
        if (args.size() % 2 != 0)
        {
          throw invalid_argument("initializer_list should "
            "contain even number of elements.");
        }
        mSequence.reserve(args.size());
        for (const auto& value : args)
        {
          mSequence.push_back(value);
        }
      }

      void dump() const
      {
        for (const auto& value : mSequence) {
          cout << value << ", ";
        }
        cout << endl;
      }

    private:
      vector<double> mSequence;
    };

  }
  void ch08DemoInitializerListCtor()
  {
    FUNC_INFO;
    InitializerListCtor::EvenSequence p1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    p1.dump();

    try {
      InitializerListCtor::EvenSequence p2 = { 1.0, 2.0, 3.0 };
    }
    catch (const invalid_argument& e) {
      cout << e.what() << endl;
    }
  }

  void ch08DemoCopyAssignment()
  {
    FUNC_INFO;
    chap08::SpreadsheetCell myCell, anotherCell, aThirdCell;

    myCell = anotherCell = aThirdCell;
    myCell.operator=(anotherCell.operator=(aThirdCell));

    chap08::SpreadsheetCell cell(4);
    cell = cell; // self-assignment
  }

  namespace DeleteConstructor {
    class LLL {
    public:
      static int square(int x) { return x * x; }
      ~LLL() = delete;
    };
  }
  void ch08DemoExplicitlyDeletedConstructors()
  {
    // DeleteConstructor::LLL a; // error cannot delete object
    printf("square = %d\n", DeleteConstructor::LLL::square(2));
  }

  void ch08DemoCpp17AsconstRemoveconstAndReference()
  {
    FUNC_INFO;
    std::string mutableString = "Hello World!";
    const std::string& constView = std::as_const(mutableString);

    /*
    *   template <class T>
    *   constexpr std::add_const_t<T>& as_const(T& t) noexcept;
    *
    *   template <class T>
    *   void as_const(const T&&) = delete;
    */

    assert(&constView == &mutableString);
    assert(&std::as_const(mutableString) == &mutableString);

    using WhatTypeIsIt = std::remove_reference_t<decltype(std::as_const(mutableString))>;

    static_assert(std::is_same<std::remove_const_t<WhatTypeIsIt>, std::string>::value,
      "WhatTypeIsIt should be some kind of string.");
    static_assert(!std::is_same< WhatTypeIsIt, std::string >::value,
      "WhatTypeIsIt shouldn't be a mutable string.");
  }


  namespace DeletingOverload
  {
    class Base
    {
    public:
      void func(int x) {}
      void func(double x) = delete;
    };
    class Sub : public Base
    {
    public:
      void func(int x) = delete;
      void func(double x) {}
    };


    class Spreadsheet2
    {
    private:
      static inline size_t sCounter = 0; // inline static member
    };

  }
  void ch08DemoExplicitlyDeletingOverloads()
  {
    DeletingOverload::Base b;
    // b.func(1.2); // compiler error, can not call deleted function
    b.func(1); // OK

    DeletingOverload::Sub s;
    s.func(1.2);
    // s.func(2); // compiler error, can not call deleted function
  }
}
