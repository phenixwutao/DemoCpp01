// DemoCppNewStandard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "P01_Basic_New_Features\P01_Basic_New_Features.h"

int main()
{
  BasicNewFeatures::DemoBasicForLoop();
  BasicNewFeatures::DemoNullptr();
  BasicNewFeatures::DemoTemplateFunctionNullptr();
  BasicNewFeatures::DemoUnicodeSupport();
  BasicNewFeatures::DemoRawString();
  BasicNewFeatures::DemoUniformInitializationSyntax();

  return 0;
}

