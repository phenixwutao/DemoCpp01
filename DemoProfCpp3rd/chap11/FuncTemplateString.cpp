#include "StdAfx.h"
#include "FuncTemplateString.h"

// Function template specializatiom
template<>
size_t Find<const char*>(const char*& value, const char** arr, size_t wSize)
{
  printf("Specialization\n");
  for (size_t i = 0; i < wSize; i++)
  {
    if (strcmp(value, arr[i]) == 0)
      return i;
  }
  return NOT_FOUND;
}
size_t Find(const char*& value, const char** arr, size_t size)
{
  printf("Overload\n");
  for (size_t i = 0; i < size; i++) {
    if (strcmp(arr[i], value) == 0) {
      return i; // Found it; return the index
    }
  }
  return NOT_FOUND; // Failed to find it; return NOT_FOUND
}
