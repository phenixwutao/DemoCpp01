#include "stdafx.h"

#include "SpreadsheetCell.h"
#include "chap14OperatorOverloading.h"

void chap14TestArithmeticOperators()
{
  SpreadsheetCell c1(4);
  SpreadsheetCell c2(4);
  SpreadsheetCell c3;

  c1++;
  ++c2;
  c3 = -c1;
}
