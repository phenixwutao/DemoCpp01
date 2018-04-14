#pragma once

#include "SpreadsheetCell10.h"
#include <optional>

namespace chap10
{
  class DoubleSpreadsheetCell : public SpreadsheetCell
  {
  public:
    virtual void set(double inDouble);
    virtual void set(std::string_view inString) override;

    virtual std::string getString() const override;

  private:
    static std::string doubleToString(double inValue);
    static double stringToDouble(std::string_view inValue);

    std::optional<double> mValue; // C++17 std::optional template class
  };
}