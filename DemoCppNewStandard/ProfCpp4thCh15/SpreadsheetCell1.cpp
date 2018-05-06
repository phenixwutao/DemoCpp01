#include "stdafx.h"
#include "SpreadsheetCell1.h"
#include <stdexcept>

using namespace std;

namespace Tut1 {

  SpreadsheetCell::SpreadsheetCell(double initialValue)
    : mValue(initialValue)
  {
  }

  SpreadsheetCell::SpreadsheetCell(string_view initialValue)
    : mValue(stringToDouble(initialValue))
  {
  }

  void SpreadsheetCell::set(double inValue)
  {
    mValue = inValue;
  }

  void SpreadsheetCell::set(string_view inString)
  {
    mValue = stringToDouble(inString);
  }

  string SpreadsheetCell::doubleToString(double inValue)
  {
    return to_string(inValue);
  }

  double SpreadsheetCell::stringToDouble(string_view inString)
  {
    return strtod(inString.data(), nullptr);
  }

  SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return SpreadsheetCell(lhs.getValue() + rhs.getValue());
  }

  SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return SpreadsheetCell(lhs.getValue() - rhs.getValue());
  }

  SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return SpreadsheetCell(lhs.getValue() * rhs.getValue());
  }

  SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    if (rhs.getValue() == 0) {
      throw invalid_argument("Divide by zero.");
    }
    return SpreadsheetCell(lhs.getValue() / rhs.getValue());
  }

  SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs)
  {
    set(getValue() + rhs.getValue());
    return *this;
  }

  SpreadsheetCell& SpreadsheetCell::operator-=(const SpreadsheetCell& rhs)
  {
    set(getValue() - rhs.getValue());
    return *this;
  }

  SpreadsheetCell& SpreadsheetCell::operator*=(const SpreadsheetCell& rhs)
  {
    set(getValue() * rhs.getValue());
    return *this;
  }

  SpreadsheetCell& SpreadsheetCell::operator/=(const SpreadsheetCell& rhs)
  {
    if (rhs.getValue() == 0) {
      throw invalid_argument("Divide by zero.");
    }
    set(getValue() / rhs.getValue());
    return *this;
  }

  bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return (lhs.getValue() == rhs.getValue());
  }

  bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return (lhs.getValue() < rhs.getValue());
  }

  // minus operator
  SpreadsheetCell SpreadsheetCell::operator-() const
  {
    return SpreadsheetCell(-getValue());
  }

  // pre-increment ++i operator
  SpreadsheetCell& SpreadsheetCell::operator++()
  {
    set(getValue() + 1);
    return *this;
  }

  // post-increment operator i++
  SpreadsheetCell SpreadsheetCell::operator++(int)
  {
    auto oldCell(*this); // Save current value
    ++(*this);           // Increment using prefix ++
    return oldCell;      // Return the old value
  }

  // pre-decrement --i operator
  SpreadsheetCell& SpreadsheetCell::operator--()
  {
    set(getValue() - 1);
    return *this;
  }

  // post-decrement i-- operator
  SpreadsheetCell SpreadsheetCell::operator--(int)
  {
    auto oldCell(*this); // Save current value
    --(*this);           // Decrement using prefix --
    return oldCell;      // Return the old value
  }

  bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return (lhs.getValue() > rhs.getValue());
  }

  bool operator!=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return (lhs.getValue() != rhs.getValue());
  }

  bool operator<=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return (lhs.getValue() <= rhs.getValue());
  }

  bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
  {
    return (lhs.getValue() >= rhs.getValue());
  }

  // overloading extraction operator
  ostream& operator<<(ostream& ostr, const SpreadsheetCell& cell)
  {
    ostr << cell.getValue();
    return ostr;
  }

  // overloading insertion operator
  istream& operator>>(istream& istr, SpreadsheetCell& cell)
  {
    double value;
    istr >> value;
    cell.set(value);
    return istr;
  }
}
