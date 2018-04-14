#include "stdafx.h"
#include "StringSpreadsheetCell10.h"

using namespace std;
namespace chap10 {

  StringSpreadsheetCell::StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell)
  {
    mValue = inDoubleCell.getString();
  }

  void StringSpreadsheetCell::set(string_view inString)
  {
    mValue = inString;
  }

  string StringSpreadsheetCell::getString() const
  {
    return mValue.value_or("");
  }
}