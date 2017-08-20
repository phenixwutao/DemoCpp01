#include "stdafx.h"

#include "chap11Template.h"

void chap11DemoGrid()
{
  Grid<int> myIntGrid; // declares a grid that stores ints,
                       // using default parameters for the constructor
  myIntGrid.printElements();

  Grid<double> myDoubleGrid(11, 11); // declares an 11x11 Grid of doubles
  myIntGrid.setElementAt(0, 0, 10);
  myDoubleGrid.printElements();

  int x = myIntGrid.getElementAt(0, 0);
  Grid<int> grid2(myIntGrid); // Copy constructor
  Grid<int> anotherIntGrid;
  anotherIntGrid = grid2; // Assignment operator

  grid2.printElements();
  anotherIntGrid.printElements();

  Grid<const char*> stringGrid1(2, 2); // Uses const char* specialization
  const char* dummy = "dummy";
  stringGrid1.setElementAt(0, 0, "hello");
  stringGrid1.setElementAt(0, 1, dummy);
  stringGrid1.setElementAt(1, 0, dummy);
  stringGrid1.setElementAt(1, 1, "there");
  stringGrid1.printElements();

  Grid<int> gr5(2,2);
  gr5.setElementAt(0, 0, 2);
  gr5.setElementAt(0, 1, 2);
  gr5.setElementAt(1, 0, 2);
  gr5.setElementAt(1, 1, 2);

  Grid<int> gr6(2, 3);
  gr6.setElementAt(0, 0, 3);
  gr6.setElementAt(0, 1, 3);
  gr6.setElementAt(0, 2, 3);
  gr6.setElementAt(1, 0, 3);
  gr6.setElementAt(1, 1, 3);
  gr6.setElementAt(1, 2, 3);

  auto gr7 = gr5 + gr6;
  printf("print gr7 after + operation\n");
  gr7.printElements();
}

namespace
{
  constexpr size_t GetCurrentWidth()
  {
    return 2;
  }
}

void chap11DemoGridNonTypeParam()
{
  GridNonTypeParam<int, 3, 4> grid1;
  grid1.setElementAt(1, 1, 15);
  grid1.printElements();
  GridNonTypeParam<int, 3, 4> grid2;
  grid2 = grid1;
  grid2.printElements();

  // Non-type parameters should be const or constexpr
  GridNonTypeParam<int, GetCurrentWidth(), 4> grid3;
  const size_t kCurrentHeight = 4;
  GridNonTypeParam<int, GetCurrentWidth(), kCurrentHeight> grid4;

  // use defaults for template parameters
  GridNonTypeParam<double> grid5;
  grid5.setElementAt(3, 3, 0.99);
  grid5.printElements();

  //copy from double to int instantiated class object
  GridNonTypeParam<int, 3, 3> grid6;
  grid6.setElementAt(2, 2, 9);
  GridNonTypeParam<double, 3, 3> grid7;
  grid7 = grid6;
  printf("print grid7\n");
  grid7.printElements();

  //template<typename T, size_t WIDTH, size_t HEIGHT>
  using GridDouble = GridNonTypeParam<double, 3, 3>;
  GridDouble grid8;
  grid8.setElementAt(1, 1, 5.306);
  grid8.printElements();
}

void chap11FunctionTemplatesSyntax()
{
  // explicitly specifying the type
  auto wOut1 = MyFunc1<double, double>(1.1, 1.2);
  auto wOut2 = MyFunc2<double, double>(1.1, 1.2);

  // the compiler deduce it from the arguments
  auto wOut3 = MyFunc1(1.1, 1.2);
  auto wOut4 = MyFunc2(1.1, 1.2);

  printf("wOut1=%f, wOut2=%f\n", wOut1, wOut2);
  printf("wOut3=%f, wOut4=%f\n", wOut3, wOut4);

  int x = 3, intArr[] = { 1, 2, 3, 4 };
  size_t sizeIntArr = sizeof(intArr) / sizeof(int);
  auto res1 = Find(x, intArr, sizeIntArr);      // calls Find<int> by deduction
  auto res2 = Find<int>(x, intArr, sizeIntArr); // calls Find<int> explicitly
  printf("res1 %zu, res2 %zu\n", res1, res2);

  size_t res3 = Find(x, intArr);
  printf("res3 %zu \n", res3);
}

void chap11FunctionTemplateSpecialization1()
{
  const char* word = "two";
  const char* arr[] = { "one", "two", "three", "four" };
  size_t sizeArr = sizeof(arr) / sizeof(arr[0]);
  auto res1 = Find<const char*>(word, arr, sizeArr);// Calls const char* specialization
  auto res2 = Find(word, arr, sizeArr);             // Calls const char* specialization if no template overloading
  printf("res1 %zu, res2 %zu\n", res1, res2);
}

void chap11FunctionTemplateSpecialization2()
{
  const char* word = "two";
  const char* arr[] = { "one", "two", "three", "four" };
  size_t sizeArr = sizeof(arr) / sizeof(arr[0]);
  size_t res;
  res = Find<const char*>(word, arr, sizeArr);// Calls const char* specialization
  res = Find(word, arr, sizeArr);             // Calls template overloading
  res = Find(word, arr);						          // Calls template overloading
  if (res != NOT_FOUND)
    cout << res << endl;
  else
    cout << "Not found" << endl;

}
