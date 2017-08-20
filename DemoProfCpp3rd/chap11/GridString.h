#pragma once
#include <cstddef>
#include <string>

#include "Grid.h"

// class template specialization with const char*
// need to 
template <>
class Grid<const char*>
{
public:
  explicit Grid(size_t inWidth = kDefaultWidth, size_t inHeight = kDefaultHeight);
  virtual ~Grid();

  void setElementAt(size_t x, size_t y, const char* InElem);
  const char* getElementAt(size_t x, size_t y) const;
  void printElements();

  size_t getWidth() const { return mWidth; }
  size_t getHeight() const { return mHeight; }
  static const size_t kDefaultWidth = 10;
  static const size_t kDefaultHeight = 10;

private:
  void initializeCellsContainer();
  std::vector<std::vector<std::string>> mCells;
  size_t mWidth, mHeight;
};

Grid<const char*>::Grid(size_t inWidth, size_t inHeight)
  : mWidth(inWidth), mHeight(inHeight)
{
  initializeCellsContainer();
}

Grid<const char*>::~Grid()
{
  mCells.clear();
}

void Grid<const char*>::initializeCellsContainer()
{
  mCells.resize(mWidth);
  for (auto& column : mCells)
  {
    column.resize(mHeight);
  }
}

void Grid<const char*>::setElementAt(size_t x, size_t y, const char* InElem)
{
  mCells[x][y] = (InElem !=nullptr) ? InElem: "";
}


const char* Grid<const char*>::getElementAt(size_t x, size_t y) const
{
  return mCells[x][y].c_str();
}

void Grid<const char*>::printElements()
{
  for (const auto& col : mCells)
  {
    for (const auto& cell : col)
      printf("%s, ", cell.c_str());
    printf("\n");
  }
}
