// DemoProfCpp3rd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "chap19\chap19.h"
#include "chap11\chap11Template.h"
#include "chap12\chap12OutputStreams.h"
#include "chap13\chap13HandleException.h"
#include "chap14\chap14OperatorOverloading.h"
#include "chap23\chap23MultiThreadProgramming.h"
#include "ModernCpp\ModernCpp.h"

int main(int argc, char* argv[])
{
  printf("------------------------------------\n");
  printf("Professional C++ 3rd!\n");
  printf("LZA 520 2017\n");
  printf("------------------------------------\n");
  //chap19StdFunction();
  //chap19StdFunctionLambda();
  //chap11DemoGrid();
  //chap11DemoGridNonTypeParam();
  //chap11FunctionTemplatesSyntax();
  //chap11FunctionTemplateSpecialization1();
  //chap11FunctionTemplateSpecialization2();
  //chap12TestStreams();
  //chap12TestManipulators();
  //chap12TestInputGet();
  //chap12TestInputUnget();
  //chap12TestInputPeek();
  //chap12TestInputGetline();
  //chap12TestInputErrorCheck();
  //chap12TestMuffin();
  //chap12TestStringStream();
  //chap12TestOutputFileStream(argc, argv);
  //chap12TestJumpingWithSeekTell();
  //chap12TestLinkStream();
  //chap12TestBidirectionalIO();
  //chap13TestThrowException();
  //chap13TestMultipleExceptions();
  //chap13TestMultipleExceptionsTwoTypes();
  //chap13TestUnspecifiedExceptions();
  //chap13TestUncaughtExceptions();
  //chap13TestThrowList();
  //chap13TestUnspecifiedExceptions();
  //chap13TestExtendExceptionClass();
  //chap13TestStackUnwindSmartPointers();
  //chap13TestStackUnwindCatchThrow();
  //chap13TestErrorHandleMemoryAlloc();
  //chap13TestErrorHandleNoThrow();
  //chap13TestErrorHandleNewHandler();
  //chap13TestErrorHandleConstructorTryBlocks();
  //chap14TestArithmeticOperators();
  //chap14TestSubscriptOperators();
  //chap14TestFunctors();
  //chap14TestPointerOperators();
  //chap14TestConversionOperators();
  //chap14TestNewDeleteOperators();

  //chap23TestThreadWithFunctionPointer();
  //chap23TestThreadWithFunctionObject();
  //chap23TestThreadWithLambda();
  //chap23TestThreadWithExceptions();
  //chap23TestThreadLocalStorage();
  //chap23TestNonAtomicOperation();
  //chap23TestAtomicOperation();
  //chap23TestAtomicOperationOptimised();
  //chap23TestAtomicFetchAdd();
  //chap23TestThreadCallOnce();
  //chap23TestThreadFunctionObjectWithMutex();
  //chap23TestThreadTimedLock();
  //chap23TestThreadDoubleCheckedLocking();
  //chap23TestFuturePackedTask();
  //chap23TestFutureAsynch();
  //chap23TestAsynchErrorHandling();
  //chap23TestLogger();

  // modern cpp demo functions
  ModernCppDemoAuto();
  ModernCppDemoAlias();
  ModernCppDemoInitializerList();
  ModernCppDemoNonStaticMemberInitialization();
  ModernCppDemoAlignment();
  ModernCppDemoScopedEnumerations();
  ModernCppDemoOverride_Final_For_Virtual_Methods();

  return EXIT_SUCCESS;
}

