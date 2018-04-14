#pragma once

#include "CherryTree.h"
#include "BingCherry.h"

namespace Chap10 {
  class BingCherryTree : public CherryTree
  {
  public:
    virtual BingCherry* pick() override;
  };
}
