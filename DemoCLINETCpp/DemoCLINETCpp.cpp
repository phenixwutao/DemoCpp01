// DemoCLINETCpp.cpp : main project file.

#include "stdafx.h"
#include <iostream>

using namespace System;

int main(array<System::String ^> ^args)
{
  Console::ForegroundColor = ConsoleColor::Cyan; // normal display color
  Console::WriteLine(L"Hello World");
  Console::ResetColor();

  Console::ForegroundColor = ConsoleColor::Magenta; // error color
  Console::WriteLine(L"Hello World");
  Console::ResetColor();

  Console::ForegroundColor = ConsoleColor::Yellow; // highlight or warning color
  Console::WriteLine(L"Hello World");
  Console::ResetColor();

  system("pause");
  return 0;
}
