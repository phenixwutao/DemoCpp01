#pragma once

#include <stdexcept>

template<typename T>
class Array
{
public:
  Array();
  virtual ~Array();
  Array<T>& operator=(const Array<T>& rhs) = delete;
  Array(const Array<T>& rhs) = delete;

  T& operator[](size_t i);
  const T& operator[](size_t i) const;
  T getElementAt(size_t i) const;
  void setElementAt(size_t i, const T &value);

private:
  constexpr static const size_t kAllocSize = 4;
  void resize(size_t newSize);
  // Sets all elements to 0
  void initializeElements();
  T* m_pElems;
  size_t m_wSize;
};

template<typename T>
Array<T>::Array()
{
  m_wSize = kAllocSize;
  m_pElems = new T[m_wSize];
  initializeElements();
}

template<typename T>
Array<T>::~Array()
{
  delete[] m_pElems;
  m_wSize = 0;
  m_pElems = nullptr;
}

template<typename T>
T & Array<T>::operator[](size_t i)
{
  if (m_wSize <= i)
    resize(i+ m_wSize);
  return m_pElems[i];
}

template<typename T>
const T & Array<T>::operator[](size_t i) const
{
  if (m_wSize <= i)
    throw std::out_of_range("element is out of range!");
  return m_pElems[i];
}

template<typename T>
T Array<T>::getElementAt(size_t i) const
{
  if (i >= m_wSize)
    throw std::out_of_range("element is out of range!");
  return m_pElems[i];
}

template<typename T>
void Array<T>::setElementAt(size_t i, const T &value)
{
  if (i >= m_wSize)
    throw std::out_of_range("element is out of range!");
  m_pElems[i] = value;
}

template<typename T>
inline void Array<T>::initializeElements()
{
  for (size_t i = 0; i < m_wSize; i++)
    m_pElems[i] = T();
}

template<typename T>
inline void Array<T>::resize(size_t newSize)
{
  T* poldElems = m_pElems;
  size_t woldSize = m_wSize;
  m_wSize = newSize;
  m_pElems = new T[m_wSize];

  initializeElements();

  for (size_t i = 0; i < woldSize; i++)
    m_pElems[i] = poldElems[i];

  if (poldElems != nullptr)
    delete[] poldElems;

  cout << "resize elements: ";
  for (size_t i = 0; i < m_wSize; i++)
    cout << m_pElems[i] << " ";
  cout << endl;

}

