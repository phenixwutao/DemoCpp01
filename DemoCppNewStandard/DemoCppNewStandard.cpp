// DemoCppNewStandard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "P01_Basic_New_Features\P01_Basic_New_Features.h"
#include "P02_New_Libs_Enhancement\P02_New_Libs_Enhancement.h"

int main()
{
  //BasicNewFeatures::DemoBasicForLoop();
  //BasicNewFeatures::DemoNullptr();
  //BasicNewFeatures::DemoTemplateFunctionNullptr();
  //BasicNewFeatures::DemoUnicodeSupport();
  //BasicNewFeatures::DemoRawString();
  //BasicNewFeatures::DemoUniformInitializationSyntax();
  //BasicNewFeatures::DemoInitializerLists();
  //BasicNewFeatures::DemoLambdaFunctions();
  //BasicNewFeatures::DemoLambdaCapturingClassMembers();
  //BasicNewFeatures::DemoLambdaReturnTypes();
  //BasicNewFeatures::DemoLambdaWithoutParameterLists();
  //BasicNewFeatures::DemoLambdaStoringClosures();
  //BasicNewFeatures::DemoLambdasAsContainerComparisonFunctions();
  //BasicNewFeatures::DemoUsingVersusTypedef();
  //BasicNewFeatures::DemoBasicThreads();
  //BasicNewFeatures::DemoBasicThreadLifetime();
  //BasicNewFeatures::DemoThreadAsynchronousCall();
  //BasicNewFeatures::DemoThreadFuture();
  //BasicNewFeatures::DemoThreadFutureWaitFor();
  //BasicNewFeatures::DemoThreadFutureVoid();

  NewLibsEnhancement::DemoUniquePointer();
  NewLibsEnhancement::DemoUniquePointerMoveObject();
  NewLibsEnhancement::DemoForwardList();
  NewLibsEnhancement::DemoRegularExpression();


  return 0;
}

