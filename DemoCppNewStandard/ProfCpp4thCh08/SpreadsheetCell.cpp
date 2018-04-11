#include "stdafx.h"
#include "SpreadsheetCell.h"

using namespace std;
namespace chap08
{
  SpreadsheetCell::SpreadsheetCell(double initialValue)
    : mValue(initialValue)
  {
  }

  SpreadsheetCell::SpreadsheetCell(string_view initialValue)
    : mValue(stringToDouble(initialValue))
  {
  }

  SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
    : mValue(src.mValue)
  {
    printf("calling SpreadsheetCell copy ctor\n");
  }

  SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
  {
    if (this != &rhs)
    {
      mValue = rhs.mValue;
    }
    printf("calling SpreadsheetCell::operator=\n");
    return *this;
  }

  void SpreadsheetCell::setValue(double inValue)
  {
    mValue = inValue;
  }

  double SpreadsheetCell::getValue() const
  {
    return mValue;
  }

  void SpreadsheetCell::setString(string_view inString)
  {
    mValue = stringToDouble(inString);
  }

  string SpreadsheetCell::getString() const
  {
    return doubleToString(mValue);
  }

  string SpreadsheetCell::doubleToString(double inValue) const
  {
    return to_string(inValue);
  }

  double SpreadsheetCell::stringToDouble(string_view inString) const
  {
    return strtod(inString.data(), nullptr);
  }
}