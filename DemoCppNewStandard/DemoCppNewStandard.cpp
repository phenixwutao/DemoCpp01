// DemoCppNewStandard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "P01_Basic_New_Features\P01_Basic_New_Features.h"
#include "P02_New_Libs_Enhancement\P02_New_Libs_Enhancement.h"
#include "P03_New_Class_Features\P03_New_Class_Features.h"
#include "P04_New_Library_Features\P04_New_Library_Features.h"

#include "ProfCpp4thCh01\ProfCpp4thCh01.h"

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

  //NewLibsEnhancement::DemoUniquePointer();
  //NewLibsEnhancement::DemoUniquePointerMoveObject();
  //NewLibsEnhancement::DemoForwardList();
  //NewLibsEnhancement::DemoRegularExpression();
  //NewLibsEnhancement::DemoCallableEntity();
  //NewLibsEnhancement::DemoUsingStdFunction();
  //NewLibsEnhancement::DemoBindBasis();
  //NewLibsEnhancement::DemoBindClassFunction();
  //NewLibsEnhancement::DemoBindPositions();

  //NewClassFeatures::DemoCopyMoveObject();
  //NewClassFeatures::DemoMoveClassHierarchy();
  //NewClassFeatures::DemoForwarding();
  //NewClassFeatures::DemoClassDefaultMemberFunctions();
  //NewClassFeatures::DemoInheritingConstructors();

  //NewLibraryFeatures::DemoStaticAssert();
  //NewLibraryFeatures::DemoConversionOperator();
  //NewLibraryFeatures::DemoDeclType();
  //NewLibraryFeatures::DemoVirtualFunctions();

  chap01::ch01Typetest();
  chap01::ch01DemoNamespaceCpp17();
  chap01::ch01DemoEnumClass();
  chap01::ch01DemoSwitchFallthrough();
  chap01::ch01DemoFunctionReturnTypeDeduction();
  chap01::ch01DemoArrayInitializationSize();

  return 0;
}

