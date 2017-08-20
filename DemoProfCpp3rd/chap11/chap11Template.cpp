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

}

