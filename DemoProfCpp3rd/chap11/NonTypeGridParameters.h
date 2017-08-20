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

  // Class Method Template with Non-Type Parameters
  template<typename E, size_t WIDTH2, size_t HEIGHT2>
  GridNonTypeParam(const GridNonTypeParam<E, WIDTH2, HEIGHT2>& src);

  template <typename E, size_t WIDTH2, size_t HEIGHT2>
  GridNonTypeParam<T, WIDTH, HEIGHT>& operator=(const GridNonTypeParam<E, WIDTH2, HEIGHT2>& rhs);

private:
  T mCells[WIDTH][HEIGHT];

  template<typename E, size_t WIDTH2, size_t HEIGHT2>
  void CopyFrom(const GridNonTypeParam<E, WIDTH2, HEIGHT2>& src);
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

template<typename T, size_t WIDTH, size_t HEIGHT>
template<typename E, size_t WIDTH2, size_t HEIGHT2>
GridNonTypeParam<T, WIDTH, HEIGHT>::GridNonTypeParam(const GridNonTypeParam<E, WIDTH2, HEIGHT2>& src)
{
  CopyFrom(src);
}


template<typename T, size_t WIDTH, size_t HEIGHT>
template<typename E, size_t WIDTH2, size_t HEIGHT2>
GridNonTypeParam<T, WIDTH, HEIGHT>& GridNonTypeParam<T, WIDTH, HEIGHT>::operator=(const GridNonTypeParam<E, WIDTH2, HEIGHT2>& rhs)
{
  CopyFrom(rhs);
  return *this;
}

template<typename T, size_t WIDTH, size_t HEIGHT>
template<typename E, size_t WIDTH2, size_t HEIGHT2>
void GridNonTypeParam<T, WIDTH, HEIGHT>::CopyFrom(const GridNonTypeParam<E, WIDTH2, HEIGHT2>& src)
{
  for (size_t i = 0; i < WIDTH; i++)
  {
    for (size_t j = 0; j < HEIGHT; j++)
    {
      if (i < WIDTH2 && j < HEIGHT2)
      {
        mCells[i][j] = src.getElementAt(i, j);
      }
      else
      {
        mCells[i][j] = T();
      }
    }
  }
}
