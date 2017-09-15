// POSIXThreads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DemoPThread\DemoPThread.h"

int main()
{
  TestHelloProgram();

  TestThreadCreation();

  TestSimpleThread();

  TestSimpleMutex();

  TestThreadOnceOnly();

  TestThreadIDs();

  TestThreadExitStatus();

  TestTimedMutexLock();

  return 0;
}

