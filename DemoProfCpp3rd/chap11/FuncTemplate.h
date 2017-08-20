#pragma once
#include <iostream>
using namespace std;

template<typename T1, typename T2>
auto MyFunc1(const T1& r1, const T2& r2)
{
  return (r1 + r2);
}

template<typename T1, typename T2>
auto MyFunc2(const T1& r1, const T2& r2) -> decltype(r1 + r2)
{
  return (r1 + r2);
}

static const size_t NOT_FOUND = (size_t)(-1);
template<typename T>
size_t Find(T& value, T* arr, size_t wSize)
{
  for (size_t i = 0; i < wSize; i++)
  {
    if (arr[i] == value)
      return i;
  }
  return NOT_FOUND;
}

template <typename T, size_t SIZE>
size_t Find(T& value, T(&arr)[SIZE])
{
  return Find(value, arr, SIZE);
}

// function template specialization
template<>
size_t Find<const char*>(const char*& value, const char** arr, size_t wSize);

// function template overloading
size_t Find(const char*& value, const char** arr, size_t size);