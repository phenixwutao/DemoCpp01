#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>

using namespace std::rel_ops;
namespace Tut1 {
  class SpreadsheetCell
  {
  public:
    SpreadsheetCell() = default;
    SpreadsheetCell(double initialValue);
    explicit SpreadsheetCell(std::string_view initialValue);

    void set(double inValue);
    void set(std::string_view inString);

    double getValue() const { mNumAccesses++; return mValue; }
    std::string getString() const { mNumAccesses++; return doubleToString(mValue); }

    static std::string doubleToString(double inValue);
    static double stringToDouble(std::string_view inString);

    SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);

    SpreadsheetCell operator-() const;
    SpreadsheetCell& operator++();   // prefix
    SpreadsheetCell operator++(int); // postfix
    SpreadsheetCell& operator--();   // prefix 
    SpreadsheetCell operator--(int); // postfix

    // conversion operators: to double and string
    explicit operator double() const;
    operator std::string() const;


  private:
    double mValue = 0;
    mutable size_t mNumAccesses = 0;
  };

  SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);

  bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);

  bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  bool operator!=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  bool operator<=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
  std::ostream& operator<<(std::ostream& ostr, const SpreadsheetCell& cell);
  std::istream& operator>>(std::istream& istr, SpreadsheetCell& cell);

}
