#pragma once

#include "SpreadsheetCell10.h"
#include <optional>
#include "DoubleSpreadsheetCell10.h"

namespace chap10 {

  class StringSpreadsheetCell : public SpreadsheetCell
  {
  public:
    StringSpreadsheetCell() = default;
    StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell);

    virtual void set(std::string_view inString) override;

    virtual std::string getString() const override;

  private:
    std::optional<std::string> mValue;
  };
}