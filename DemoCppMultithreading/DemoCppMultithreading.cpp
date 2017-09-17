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

  chap05TestAtomicOperation();

  //C11ThreadThreeWaysCreateThreads();
  //C11ThreadJoinDetach();
  C11ThreadJoinDetachException();
  C11ThreadPassingArguments();
  C11ThreadShareDataMutexLock();
  C11ThreadConditionVariable();

  return EXIT_SUCCESS;
}

