#include "stdafx.h"
#include "BingCherryTree.h"
#include <memory>

namespace Chap10 {

  BingCherry* BingCherryTree::pick()
  {
    auto theCherry = std::make_unique<BingCherry>();
    theCherry->polish();
    return theCherry.release();
  }
}
