#pragma once

#include <string>
#include <string_view>

namespace chap10
{
  class SpreadsheetCell
  {
  public:
    virtual ~SpreadsheetCell() = default;

    virtual void set(std::string_view inString) = 0;

    virtual std::string getString() const = 0;
  };
}
