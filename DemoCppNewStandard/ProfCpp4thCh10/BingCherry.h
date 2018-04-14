#pragma once

#include "Cherry.h"

namespace Chap10 {
  class BingCherry : public Cherry
  {
  public:
    virtual void printType() override;

    virtual void polish();
  };
}
