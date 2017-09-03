// DemoCppMultithreading.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "chap01\chap01DemoHello.h"
#include "chap02\chap02DemoThreadManagement.h"

int main()
{
  chap01DemoHello();
  chap02ThreadStart();
  chap02ThreadInvalidReferenceFix();
  chap02TestThreadGuard();
  chap02TestDaemonThreads();

  return EXIT_SUCCESS;
}

