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

#include "DongShanHai\DongShanHai.h"

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
#if 0
  Ch01_DemoAuto();
  Ch01_DemoAlias();
  Ch01_DemoInitializerList();
  Ch01_DemoNonStaticMemberInitialization();
  Ch01_DemoAlignment();
  Ch01_DemoScopedEnumerations();
  Ch01_DemoOverride_Final_For_Virtual_Methods();
  Ch01_DemoRangeBasedForLoop();
  Ch01_DemoEnableRangeBasedForLoop4CustomTypes();
  Ch01_DemoCheckModules();
  Ch01_DemoExplicitConstructorAndConversionOperator();
  Ch01_DemoNamespace();
  Ch01_DemoNamespacesForSymbolVersioning();
  Ch01_DemoStructuredBindings();

  Ch02_DemoConvertingNumericStringTypes();
  Ch02_DemoNumberLimitsOtherProperties();
  Ch02_DemoGeneratingPseudoRandomNumbers();
  //Ch02_DemoMonteCarloSimulation();
  Ch02_DemoStandardLiteralOperators();
  Ch02_DemoCreatingCookedUserDefinedLiterals();
  Ch02_DemoCreatingRawUserDefinedLiterals();
  Ch02_DemoCreatingStringLibraryHelpers();
  Ch02_DemoStringUsingRegularExpressions();
  Ch02_DemoParsingStringContentUsingRegularExpressions();
  Ch02_DemoReplacingStringContentUsingRegularExpressions();
  Ch02_DemoUsingStringViewInsteadConstantStringReferences();

  //Ch08_DemoWorkingWithThreads();
  //Ch08_DemoHandlingExceptionsFromThreadFunctions();
  //Ch08_DemoSynchronizingAccessToSharedDataWithMutexesAndLocks();
  //Ch08_DemoAvoidingUsingRecursiveMutexes();
  //Ch08_DemoSendingNotificationsBetweenThreads();
  //Ch08_DemoUsingPromisesAndFuturesFromThreads();
  //Ch08_DemoExecutingFunctionsAsynchronously();
  //Ch08_DemoUsingAtomicTypes();
  //Ch08_DemoImplementingParallelMapWithThreads();
  //Ch08_DemoImplementingParallelMapWithTasks();

  Ch03_DemoDefaultedAndDeletedFunctions();
  Ch03_DemoUsingLambdasWithStandardAlgorithms();
  Ch03_DemoUsingGenericLambdas();
  Ch03_DemoWritingRecursiveLambda();
  Ch03_DemoWritingFunctionTemplateWithVariableNumberArguments();
  Ch03_DemoComposingFunctionsIntoHigherOrderFunction();
  Ch03_DemoUniformlyInvokingAnythingCallable();

  Ch04_DemoConditionallyCompiling();
  Ch04_DemoPreprocessStringificationAndConcatenation();
  Ch04_DemoPerformingCompileTimeAssertionChecks();
  Ch04_DemoConditionallyCompilingClassFunctionsWithEnable_if();
  Ch04_DemoSelectingBranchesWithConstexpr_if();
  Ch04_DemoProvidingMetadataToCompilerWithAttributes();

  Ch05_DemoUsingVectorAsDefaultContainer();
  Ch05_DemoUsingBitsetForFixedSizeSequences();
  Ch05_DemoUsingVectorBoolForBitSequences();
  Ch05_DemoFindingElementsInRange();
  Ch05_DemoSortingRange();
  Ch05_DemoInitializingRange();
  Ch05_DemoUsingSetOperationsOnRange();
  Ch05_DemoUsingIteratorsInsertNewElements();
  Ch05_DemoWritingYourOwnRandomAccessIterator();
  Ch05_DemoContainerAccessWithNonMemberFunctions();

  Ch06_DemoExpressingTimeIntervalsWithChrono();
  Ch06_DemoMeasuringFunctionExecutionTimeWithStandardClock();
  Ch06_DemoGeneratingHashValues();
  Ch06_DemoRegisteringFunctionCalledWhenProgramExitsNormally();
#endif

  // Dong cpp programming book:
  Ch06_DemoClassMemberInitializationOrder();
  Ch06_DemoStaticClassMember();
  Ch06_DemoClassMemberInInitializationList();
  Ch06_DemoStaticAndNonStaticMembers();

  return EXIT_SUCCESS;
}

