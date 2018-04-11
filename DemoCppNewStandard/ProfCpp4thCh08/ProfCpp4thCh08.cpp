#include "stdafx.h"
#include "ProfCpp4thCh08.h"
#include "SpreadsheetCell.h"

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <vector>

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
    SpreadsheetCell myCell, anotherCell, aThirdCell;

    myCell = anotherCell = aThirdCell;
    myCell.operator=(anotherCell.operator=(aThirdCell));

    SpreadsheetCell cell(4);
    cell = cell; // self-assignment
  }
}
