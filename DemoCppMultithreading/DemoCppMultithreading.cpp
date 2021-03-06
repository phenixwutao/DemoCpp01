// DemoCppMultithreading.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "chap01\chap01DemoHello.h"
#include "chap02\chap02DemoThreadManagement.h"
#include "chap03\chap03ThreadSharingData.h"
#include "chap04\Chap04SynchronizingConcurrentOperations.h"
#include "chap05\chap05MemoryModelAtomicOperation.h"
#include "WebThreadDoc\ThreadWebDoc.h"

#include "OptionsDerivativesProgramming\OptionsDerivatives.h"
#include "ParallelPractice\chap04Miltithreads.h"

#include "ConcurrencyAction2nd\Chap01List.h"
#include "ConcurrencyAction2nd\Chap02List.h"

int main()
{
  //chap01DemoHello();
  //chap02ThreadStart();
  //chap02ThreadInvalidReferenceFix();
  //chap02TestThreadGuard();
  //chap02TestDaemonThreads();
  //chap02TestThreadPassParameter();
  //chap02TestThreadPassReference(1);
  //chap02TestThreadBindFuncParameters();
  //chap02TestThreadMoveParameter();
  //chap02TestThreadScopedThread();
  //chap02TestThreadTransferFunctionOwnership();
  //chap02TestThreadTransferThreadOwnership();
  //chap02TestThreadTransferThreadOwnershipInFunction();
  //chap02TestThreadInVector();
  //chap02TestThreadConcurrentAccumulate();
  //chap02TestThreadIdentify();

  //chap03TestMutexLock();
  //chap03TestThreadsafeStack();
  //chap03TestLockMultipleMutex();
  //chap03TestHierarchicalMutex();
  //chap03TestHierarchicalMutex2();
  //chap03TestMutexOwnershipTransfer();
  //chap03TestLockGranularitySingle();

  //chap04TestWaitForEvent();
  //chap04TestConditionVariables();
  //chap04TestThredasafeQueue();
  //chap04TestFutureGetReturnValueFromAsynchTask();
  //chap04TestAsynchTaskPassingArguments();
  //chap04TestAsyncOptions();
  //chao04AssociatingTaskWithFuturePackagedTask();
  //chap04TestMakingPromise();
  //chap04TestSequentialQuickSort();
  //chap04TestParallelQuickSort();
  //chap04TestTimePoint();

  //chap05TestAtomicOperation();

  //C11ThreadThreeWaysCreateThreads();
  //C11ThreadJoinDetach();
  //C11ThreadJoinDetachException();
  //C11ThreadPassingArguments();
  //C11ThreadShareDataMutexLock();
  //C11ThreadConditionVariable();
  //C11ThreadPromiseAndFuture();
  //C11ThreadUsingAsynchWithFunctionPointer();
  //C11ThreadUsingAsynchWithFunctionObject();
  //C11ThreadUsingAsynchWithLambda();
  //C11ThreadUsingPackagedTaskWithFunction();
  //C11ThreadUsingPackagedTaskWithFunctionObject();
  //C11ThreadUsingPackagedTaskWithLambda();
  //C11ThreadPutThreadSleep();
  //C11ThreadPutSleepUntilFutureTimePoint();
  //C11ThreadStartByClassMemberFunction();
  //C11ThreadTransferOwnershipByMove();
  //C11ThreadWithMoveSemantics();
  //C11ThreadShareMemoryLockguard();
  //C11ThreadLocalStorage();

  // Options Derivatives Programming
  //OptionsDerivTestValueOptions();
  //OptionsDerivTestRandomWalks();
  //OptionsDerivTestDate();
  //OptionsDerivTestDataSource();
  //OptionsDerivTestClearingHouse();
  //OptionsDerivTestTradeObserver();
  //OptionsDerivTestFunctionalExamples();
  //OptionsDerivTestPolynomialFunction();

  //ParallelPractice::chap04HelloExample();

  ConAction2nd::Chap01LT01_Hello();
  ConAction2nd::Chap02LT01_ClassFunctor();
  ConAction2nd::Chap02LT02_PassArgumentsToFunction();
  ConAction2nd::Chap02LT02_PassReferenceToDataObject();
  ConAction2nd::Chap02LT02_MoveDataObject();
  ConAction2nd::Chap02LT02_MoveThread();
  ConAction2nd::Chap02LT02_ThreadOwnershipTransfer();
  ConAction2nd::Chap02LT02_SpawnThread();

  return EXIT_SUCCESS;
}

