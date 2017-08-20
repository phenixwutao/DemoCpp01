#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

// Forward declare Grid template.
template <typename T> class Grid;

// Prototype for templatized operator+.
template<typename T>
Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs);

template<typename T>
class Grid
{
public:
  explicit Grid(size_t inWidth = kDefaultWidth, size_t inHeight = kDefaultHeight);
  virtual ~Grid();

  void setElementAt(size_t x, size_t y, const T& InElem);
  T& getElementAt(size_t x, size_t y);
  const T& getElementAt(size_t x, size_t y) const;
  void printElements();

  size_t getWidth() const { return mWidth; }
  size_t getHeight() const { return mHeight; }
  static const size_t kDefaultWidth = 10;
  static const size_t kDefaultHeight = 10;

  friend Grid<T> operator+ <T>(const Grid<T>& lhs, const Grid<T>& rhs);

private:
  void initializeCellsContainer();
  std::vector<std::vector<T>> mCells;
  size_t mWidth, mHeight;
};

template<typename T>
Grid<T>::Grid(size_t inWidth, size_t inHeight)
  : mWidth(inWidth), mHeight(inHeight)
{
  initializeCellsContainer();
}

template<typename T>
Grid<T>::~Grid()
{
  if (mCells.size() > 0)
    mCells.clear();
}

template<typename T>
void Grid<T>::initializeCellsContainer()
{
  mCells.resize(mWidth);
  for (auto& iCell : mCells)
    iCell.resize(mHeight);
}

template<typename T>
void Grid<T>::setElementAt(size_t x, size_t y, const T& elem)
{
  mCells[x][y] = elem;
}

template<typename T>
T& Grid<T>::getElementAt(size_t x, size_t y)
{
  return mCells[x][y];
}

template<typename T>
const T& Grid<T>::getElementAt(size_t x, size_t y) const
{
  return mCells[x][y];
}

template<typename T>
void Grid<T>::printElements()
{
  for (const auto& col : mCells)
  {
    for (const auto& cell : col)
      std::cout << cell << ", ";
    printf("\n");
  }
}

template <typename T>
Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs)
{
  size_t minWidth = std::min(lhs.getWidth(), rhs.getWidth());
  size_t minHeight = std::min(lhs.getHeight(), rhs.getHeight());
  Grid<T> result(minWidth, minHeight);
  for (size_t y = 0; y < minHeight; ++y) {
    for (size_t x = 0; x < minWidth; ++x) {
      result.setElementAt(x, y, lhs.mCells[x][y] + rhs.mCells[x][y]);
    }
  }
  return result;
}