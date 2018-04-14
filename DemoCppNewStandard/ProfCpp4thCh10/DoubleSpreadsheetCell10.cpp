#include "stdafx.h"
#include "DoubleSpreadsheetCell10.h"

using namespace std;
namespace chap10
{
  void DoubleSpreadsheetCell::set(double inDouble)
  {
    mValue = inDouble;
  }

  void DoubleSpreadsheetCell::set(string_view inString)
  {
    mValue = stringToDouble(inString);
  }

  string DoubleSpreadsheetCell::getString() const
  {
    return (mValue.has_value() ? doubleToString(mValue.value()) : "");
  }

  string DoubleSpreadsheetCell::doubleToString(double inValue)
  {
    return to_string(inValue);
  }

  double DoubleSpreadsheetCell::stringToDouble(string_view inString)
  {
    return strtod(inString.data(), nullptr);
  }
}