#include "stdafx.h"
#include "ProfCpp4thCh11.h"

#include <array>
#include <chrono>
#include <complex>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <utility>
using namespace std;

namespace chap11
{
  namespace REF
  {
    std::string getString()
    {
      return "Hello world!";
    }
  }

  void chap11DemoUseReference()
  {
    FUNC_INFO;
    int x = 3, y = 4, z = 5;
    int& xRef = x;
    xRef = 10;
    //  int& emptyRef; // DOES NOT COMPILE!

    //  int& unnamedRef1 = 5;   // DOES NOT COMPILE
    const int& unnamedRef2 = 5; // Works as expected

    // std::string& string1 = getString();   // DOES NOT COMPILE
    const std::string& string2 = REF::getString(); // Works as expected

    xRef = y; // changes value of x to 4. Doesn't make xRef refer to y.

    int& zRef = z;
    zRef = xRef; // Assigns values, not references

    int* intP;
    int*& ptrRef = intP;
    ptrRef = new int;
    *ptrRef = 5;
    delete ptrRef;

    int* xPtr = &xRef; // address of a reference is pointer to value
    *xPtr = 100;
  }


  namespace UsePtr
  {
    void printIntArr(const int arr[], size_t size)
    {
      for (size_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
      }
      cout << endl;
    }

    void separateOddsAndEvens(const int arr[], size_t size,
                              int** odds, size_t* numOdds, 
                              int** evens, size_t* numEvens)
    {
      // Count the number of odds and evens
      *numOdds = *numEvens = 0;
      for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 1)
        {
          ++(*numOdds);
        }
        else
        {
          ++(*numEvens);
        }
      }

      // Allocate two new arrays of the appropriate size.
      *odds = new int[*numOdds];
      *evens = new int[*numEvens];

      // Copy the odds and evens to the new arrays
      size_t oddsPos = 0, evensPos = 0;
      for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 1)
        {
          (*odds)[oddsPos++] = arr[i];
        }
        else
        {
          (*evens)[evensPos++] = arr[i];
        }
      }
    }
  }
  void chap11DemoUsePointer()
  {
    FUNC_INFO;
    int unSplit[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* oddNums = nullptr;
    int* evenNums = nullptr;
    size_t numOdds = 0, numEvens = 0;

    UsePtr::separateOddsAndEvens(unSplit, std::size(unSplit), &oddNums, &numOdds, &evenNums, &numEvens);
    UsePtr::printIntArr(oddNums, numOdds);
    UsePtr::printIntArr(evenNums, numEvens);

    delete[] oddNums; oddNums = nullptr;
    delete[] evenNums; evenNums = nullptr;
  }

  namespace UsePair
  {
    void printVec(const vector<int>& arr)
    {
      for (const auto& i : arr) {
        cout << i << " ";
      }
      cout << endl;
    }

    pair<vector<int>, vector<int>> separateOddsAndEvens(const vector<int>& arr)
    {
      vector<int> odds, evens;
      for (const auto i : arr)
      {
        if (i % 2 == 1)
        {
          odds.push_back(i);
        }
        else
        {
          evens.push_back(i);
        }
      }
      return make_pair(odds, evens);
    }

  }
  void chap11DemoUsePair()
  {
    FUNC_INFO;
    vector<int> vecUnSplit = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto[odds, evens] = UsePair::separateOddsAndEvens(vecUnSplit);
    UsePair::printVec(odds);
    UsePair::printVec(evens);
  }

  namespace UseConst
  {
    const double PI = 3.141592653589793238462;

    void func(const int /*param*/)
    {
      // Not allowed to change param...
    }

    void constIntOne()
    {
      const int* ip;
      ip = new int[10];
      //  ip[4] = 5; // DOES NOT COMPILE!
      delete[] ip;
    }

    void constIntTwo()
    {
      int const* ip;
      ip = new int[10];
      //  ip[4] = 5; // DOES NOT COMPILE!
      delete[] ip;
    }

    void constPtrOne()
    {
      int* const ip = nullptr;
      //  ip = new int[10]; // DOES NOT COMPILE!
      ip[4] = 5;	// Error: dereferencing a null pointer
    }

    void constPtrTwo()
    {
      // const pointer pointing to non-const int type:
      int* const ip = new int[10];  // cannot change pointer
      ip[4] = 5;                    // can change the value pointing to
      delete[] ip;
    }

    void constIntPtrOne()
    {
      int const* const ip = nullptr;
    }

    void constIntPtrTwo()
    {
      const int* const ip = nullptr;
    }

    void manyLevelConst()
    {
      const int * const * const * const ip = nullptr;
    }

    class BigClass;
    void doSomething(const BigClass& /*arg*/)
    {
      // implementation here
    }
  }
  void chap11DemoUseConst()
  {
    FUNC_INFO;
    int* ip;
    ip = new int[10];
    ip[4] = 5;
    delete[] ip;

    int z;
    const int& zRef = z;
    //  zRef = 4; // DOES NOT COMPILE

    UseConst::constPtrTwo();
  }

  namespace UseConstExpr
  {
    constexpr int getArraySize()
    {
      return 32;
    }

    // If the constexpr function is a member of a class, 
    // the function cannot be virtual.
    class Rect
    {
    public:
      /*
      * The constructor body either shall be explicitly defaulted, or shall 
      * satisfy the same requirements as the body of a constexpr function.
      */
      constexpr Rect(size_t w, size_t h) : mWidth(w), mHeight(h)
      {
      }

      // Constant expressions are evaluated at compile time!
      constexpr size_t getArea() const
      {
        return mWidth * mHeight;
      }

    private:
      size_t mWidth, mHeight;
    };
  }
  void chap11DemoUseConstexpr()
  {
    FUNC_INFO;
    int K = 5;
    // int array[K]{}; // error, expression must have a const value

    int myArray[UseConstExpr::getArraySize()];	// OK
    myArray[0] = 1;

    constexpr UseConstExpr::Rect r(8, 2);
    int myArray2[r.getArea()];
    cout << std::size(myArray2) << endl;
  }

  namespace UseStatic
  {
    /*
    * The final use of the static keyword in C++ is to create local variables that 
    * retain their values between exits and entrances to their scope. 
    * A static variable inside a function is like a global variable that is only 
    * accessible from that function. Static variable inside a function is only
    * initialised once.
    */
    void performTask()
    {
      static bool initialized = false;

      if (!initialized)
      {
        cout << "initializing" << endl;
        initialized = true;
      }
    }
  }
  void chap11DemoUseStatic()
  {
    FUNC_INFO;
    UseStatic::performTask();
    UseStatic::performTask();
  }

  namespace TypeAlias
  {
    using StringVector = std::vector<std::string>;

    void processVector(const StringVector& vec)
    {
      // Body omitted
    }


    using MatchFunction = bool(*)(int, int);
    // typedef bool(*MatchFunction)(int, int);

    void findMatches(int values1[], int values2[], size_t numValues, MatchFunction matcher)
    {
      for (size_t i = 0; i < numValues; i++)
      {
        if (matcher(values1[i], values2[i]))
        {
          cout << "Match found at position " << i << " (" << values1[i] << ", " << values2[i] << ")" << endl;
        }
      }
    }

    bool intEqual(int item1, int item2)
    {
      return item1 == item2;
    }

    bool bothOdd(int item1, int item2)
    {
      return item1 % 2 == 1 && item2 % 2 == 1;
    }

    class Employee {
    public:
      int getSalary() const
      {
        return 3000;
      }
    };
  }
  void chap11DemoTypeAlias()
  {
    FUNC_INFO;
    using IntPtr = int*;
    IntPtr ptr1 = nullptr;

    TypeAlias::StringVector myVector;
    TypeAlias::processVector(myVector);

    int arr1[] = { 2, 5, 6, 9, 10, 1, 1 };
    int arr2[] = { 4, 4, 2, 9, 0, 3, 4 };
    size_t arrSize = std::size(arr1); // Pre-C++17: sizeof(arr1) / sizeof(arr1[0]);

    cout << "Calling findMatches() using intEqual():" << endl;
    TypeAlias::findMatches(arr1, arr2, arrSize, &TypeAlias::intEqual);
    cout << endl;

    cout << "Calling findMatches() using bothOdd():" << endl;
    TypeAlias::findMatches(arr1, arr2, arrSize, &TypeAlias::bothOdd);

    cout << "use MatchFunction bothOdd" << endl;
    TypeAlias::MatchFunction func;
    func = TypeAlias::intEqual;
    TypeAlias::findMatches(arr1, arr2, arrSize, func);
  }

  void chap11DemoTypeAliasClassMethod()
  {
    FUNC_INFO;
    TypeAlias::Employee employee;
    using PtrToGet = int (TypeAlias::Employee::*) () const;
    PtrToGet methodPtr = &TypeAlias::Employee::getSalary;
    cout << (employee.*methodPtr)() << endl;
  }

  void chap11DemoConstCast()
  {
    FUNC_INFO;
    std::string str = "C++";
    const std::string& constStr = std::as_const(str);
    auto a = std::as_const(str); //auto strips away reference and const qualifiers!
  }

  namespace Attribute
  {
    [[noreturn]]void func1()
    {}

    [[deprecated("Unsafe method, please use xyz")]] void func2()
    {}

    // compiler issue warning when returning value is ignored
    [[nodiscard]] int func3()
    {
      return 42;
    }

    // The [[maybe_unused]] attribute can be used to suppress the compiler from
    // issuing a warning when something is unused
    int func4(int param1, [[maybe_unused]] int param2)
    {
      return 42;
    }
  }
  void chap11DemoAttributes()
  {
    FUNC_INFO;
    // Attribute::func2(); // deprecated function

    // switch [[fallthrough]]
    int i = 2;
    switch (i)
    {
    case 0:
      [[fallthrough]];
    case 1:
      [[fallthrough]];
    case 2:
      [[fallthrough]];
      break;
    case 3:
      break;

    default:
      break;
    }
    
    Attribute::func3();
    
    Attribute::func4(1,2);
  }

  namespace UserDefinedLiteral
  {
    // (User defined) Cooked _i literal
    std::complex<long double> operator"" _i(long double d)
    {
      return std::complex<long double>(0, d);
    }

    // Raw _i literal
    //std::complex<long double> operator"" _i(const char* p)
    //{
    //    // Implementation omitted; it requires parsing the C-style
    //    // string and converting it to a complex number.
    //}


    // Cooked _s literal
    std::string operator"" _s(const char* str, size_t len)
    {
      return std::string(str, len);
    }

  }
  void chap11DemoUserDefinedLiterals()
  {
    FUNC_INFO;
    using namespace UserDefinedLiteral;
    // Cooked _i literal
    std::complex<long double> c1 = 9.634_i;
    auto c2 = 1.23_i;         // c2 has as type std::complex<long double>

                              // Cooked _s literal
    std::string str1 = "Hello World"_s;
    auto str2 = "Hello World"_s;   // str2 has as type std::string
    auto str3 = "Hello World";     // str3 has as type const char*;
  }

  void chap11DemoStandardUserDefinedLiterals()
  {
    FUNC_INFO;
    using namespace std::string_literals;
    auto myString = "Hello World"s;

    using namespace std::string_view_literals;
    auto myStringView = "Hello World"sv; // C++17

    using namespace std::chrono_literals;
    // "h", "min", "s", "ms", "us", "ns", for creating std::chrono::duration time intervals
    auto min1 = 42min;
    auto h2 = 2h;
    auto sec3 = 5s;
    auto minisec4 = 3000ms;
    auto usec5 = 30us;
    auto nanosec6 = 4000ns;

    using namespace std::complex_literals;
    auto myComplexNumber = 1.3i;

    auto val1 = 1.0F; // float
    auto val2 = 2L; // long
    auto val3 = 1.2E+02; // double
    auto val4 = 3U; // unsigned int
    auto val5 = 4; // int
  }

  void chap11DemoQueryIncludeHeader()
  {
    // C++17 macro
//#if __has_include(<optional>)
//  #include <optional>
//  #define have_optional 1
//#elif __has_include(<experimental/optional>)
//  #include <experimental/optional>
//  #define have_optional 1
//  #define experimental_optional
//#else
//  #define have_optional 0
//#endif
  }
}
