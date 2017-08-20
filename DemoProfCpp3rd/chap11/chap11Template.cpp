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

}

void chap11DemoGridNonTypeParam()
{
  GridNonTypeParam<int, 3, 4> grid1;
  grid1.setElementAt(1, 1, 15);
  grid1.printElements();
  GridNonTypeParam<int, 3, 4> grid2;
  grid2 = grid1;
  grid2.printElements();
}

