#pragma once

// class template with non-type parameters
// provide defaults for template parameters
template <typename T, size_t WIDTH = 5, size_t HEIGHT = 5>
class GridNonTypeParam
{
public:
  GridNonTypeParam();
  virtual ~GridNonTypeParam();

  void setElementAt(size_t x, size_t y, const T& inElem);
  T& getElementAt(size_t x, size_t y);
  const T& getElementAt(size_t x, size_t y) const;
  void printElements();
  size_t getHeight() const { return HEIGHT; }
  size_t getWidth() const { return WIDTH; }

private:
  T mCells[WIDTH][HEIGHT];
};

template<typename T, size_t WIDTH, size_t HEIGHT>
GridNonTypeParam<T, WIDTH, HEIGHT>::GridNonTypeParam() : mCells()
{
  // mCells are initilaized with zeros.
}

template<typename T, size_t WIDTH, size_t HEIGHT>
GridNonTypeParam<T, WIDTH, HEIGHT>::~GridNonTypeParam()
{
}

template<typename T, size_t WIDTH, size_t HEIGHT>
void GridNonTypeParam<T, WIDTH, HEIGHT>::setElementAt(size_t x, size_t y, const T& inElem)
{
  mCells[x][y] = inElem;
}

template<typename T, size_t WIDTH, size_t HEIGHT>
T& GridNonTypeParam<T, WIDTH, HEIGHT>::getElementAt(size_t x, size_t y)
{
  return mCells[x][y];
}

template<typename T, size_t WIDTH, size_t HEIGHT>
const T& GridNonTypeParam<T, WIDTH, HEIGHT>::getElementAt(size_t x, size_t y) const
{
  return mCells[x][y];
}

template<typename T, size_t WIDTH, size_t HEIGHT>
void GridNonTypeParam<T, WIDTH, HEIGHT>::printElements()
{
  for (const auto& col : mCells)
  {
    for (const auto& cell : col)
      std::cout << cell << ", ";
    printf("\n");
  }
}