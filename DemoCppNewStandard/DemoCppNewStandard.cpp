// DemoCppNewStandard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "P01_Basic_New_Features\P01_Basic_New_Features.h"
#include "P02_New_Libs_Enhancement\P02_New_Libs_Enhancement.h"
#include "P03_New_Class_Features\P03_New_Class_Features.h"
#include "P04_New_Library_Features\P04_New_Library_Features.h"

#include "ProfCpp4thCh01\ProfCpp4thCh01.h"
#include "ProfCpp4thCh02\ProfCpp4thCh02.h"
#include "ProfCpp4thCh07\ProfCpp4thCh07.h"
#include "ProfCpp4thCh08\ProfCpp4thCh08.h"
#include "ProfCpp4thCh09\ProfCpp4thCh09.h"
#include "ProfCpp4thCh10\ProfCpp4thCh10.h"

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

  //chap01::ch01Typetest();
  //chap01::ch01DemoNamespaceCpp17();
  //chap01::ch01DemoEnumClass();
  //chap01::ch01DemoSwitchFallthrough();
  //chap01::ch01DemoFunctionReturnTypeDeduction();
  //chap01::ch01DemoArrayInitializationSize();
  //chap01::ch01DemoStdArray();
  //chap01::ch01DemoStructuredBindings();
  //chap01::ch01DemoInitializerList();
  //chap01::ch01DemoSmartPointers();
  //chap01::ch01DemoUniformInitialization();

  //chap02::ch02DemoCString();
  //chap02::ch02DemoStringLengthSize();
  //chap02::ch02DemoRawStringAndConst();
  //chap02::ch02DemoStringCmpConversion();
  //chap02::ch02DemoStringViews();

  //chap07::ch07DemoArrayDeleteOnHeap();
  //chap07::ch07DemoMultiDimensionArray();
  //chap07::ch07DemoArrayAndPointer();
  //chap07::ch07DemoUniquePtr();
  //chap07::ch07DemoSharedPtr();
  //chap07::ch07DemoSharedAlias();
  //chap07::ch07DemoWeakPtr();
  //chap07::ch08DemoMoveSmartPtr();

  chap08::ch08DemoInitializerListCtor();
  chap08::ch08DemoCopyAssignment();
  chap08::ch08DemoExplicitlyDeletedConstructors();
  chap08::ch08DemoCpp17AsconstRemoveconstAndReference();
  chap08::ch08DemoExplicitlyDeletingOverloads();

  chap09::ch09DemoOperatorOverloading();
  chap10::chap10DemoClassMethodOverload();
  chap10::chap10DemoClassMethodOverride();
  chap10::chap10DemoConstructorCallVirtualMethod();
  chap10::chap10DemoPolymorphicSpreadsheet();
  chap10::chap10DemoMultiInheritance();

  return 0;
}

