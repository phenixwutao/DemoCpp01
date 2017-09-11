#include "StdAfx.h"

#include <pthread.h>
#include <cstdio>
#include <cstdlib>

#include "DemoPThread.h"

#define NUM_THREADS     5

using namespace std;

void *PrintHello(void *threadid)
{
  long tid;
  tid = (long)threadid;
  printf("Hello World! It's me, thread #%ld!\n", tid);
  void* value = nullptr;
  pthread_exit(value);
  return value;
}

void TestHelloProgram()
{
  pthread_t threads[NUM_THREADS];
  for (long t = 0; t < NUM_THREADS; t++)
  {
    printf("In main: creating thread %ld\n", t);
    int rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  /* Last thing that main() should do */
  pthread_exit(NULL);
}

