#include "StdAfx.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "DemoPThread.h"

#define NUM_THREADS     5

using namespace std;
static unsigned long iPass = 0;

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
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
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

  for (long t = 0; t < NUM_THREADS; t++)
  {
    pthread_join(threads[t], NULL);
  }
}

void *print_message_function(void *ptr)
{
  char *message;
  message = (char *)ptr;
  printf("%s \n", message);
  return (void*)ptr;
}

void TestThreadCreation()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  pthread_t thread1, thread2;
  const char *message1 = "Thread 1";
  const char *message2 = "Thread 2";

  /* Create independent threads each of which will execute function */
  int iret1 = pthread_create(&thread1, NULL, print_message_function, (void*)message1);
  if (iret1)
  {
    fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
    exit(EXIT_FAILURE);
  }

  int iret2 = pthread_create(&thread2, NULL, print_message_function, (void*)message2);
  if (iret2)
  {
    fprintf(stderr, "Error - pthread_create() return code: %d\n", iret2);
    exit(EXIT_FAILURE);
  }

  printf("pthread_create() for thread 1 returns: %d\n", iret1);
  printf("pthread_create() for thread 2 returns: %d\n", iret2);

  /* Wait till threads are complete before main continues. Unless we  */
  /* wait we run the risk of executing an exit which will terminate   */
  /* the process and all threads before the threads have completed.   */

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
}


void *do_one_thing(void *pnum_times)
{
  int i(0), j(0);

  for (i = 0; i < 4; i++) {
    printf("doing one thing\n");
    for (j = 0; j < 10000; j++)
    (*(int *)pnum_times)++;
  }

  return(NULL);
}

void *do_another_thing(void *pnum_times)
{
  int i(0), j(0);

  for (i = 0; i < 4; i++) {
    printf("doing another \n");
    for (j = 0; j < 10000; j++)
    (*(int *)pnum_times)++;
  }

  return(NULL);
}

void do_wrap_up(int one_times, int another_times)
{
  int total;

  total = one_times + another_times;
  printf("All done, one thing %d, another %d for a total of %d\n",
    one_times, another_times, total);
}

void TestSimpleThread()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  int r1 = 0, r2 = 0;
  pthread_t thread1, thread2;

  if (pthread_create(&thread1, NULL, do_one_thing, (void *)&r1) != 0)
  {
    perror("pthread_create"), exit(1);
  }

  if (pthread_create(&thread2, NULL, do_another_thing, (void *)&r2) != 0)
  {
    perror("pthread_create"), exit(1);
  }

  if (pthread_join(thread1, NULL) != 0)
  {
    perror("pthread_join"), exit(1);
  }

  if (pthread_join(thread2, NULL) != 0)
  {
    perror("pthread_join"), exit(1);
  }

  do_wrap_up(r1, r2);

  perror("TestSimpleThread test perror");
}


int r1 = 0;
int r2 = 0;
int r3 = 0;
pthread_mutex_t r3_mutex = PTHREAD_MUTEX_INITIALIZER;

void *do_one_thing_mutex(void *pnum_times)
{
  int i, j, x(0);

  pthread_mutex_lock(&r3_mutex);
  if (r3 > 0) {
    x = r3;
    r3--;
  }
  else {
    x = 1;
  }
  pthread_mutex_unlock(&r3_mutex);

  for (i = 0; i < 4; i++) {
    printf("doing one thing\n");
    for (j = 0; j < 10000; j++) x = x + i;
    (*(int *)pnum_times)++;
  }

  return(NULL);
}

void *do_another_thing_mutex(void *pnum_times)
{
  int i, j, x(0);

  pthread_mutex_lock(&r3_mutex);
  if (r3 > 0) {
    x = r3;
    r3--;
  }
  else {
    x = 1;
  }
  pthread_mutex_unlock(&r3_mutex);

  for (i = 0; i < 4; i++) {
    printf("doing another \n");
    for (j = 0; j < 10000; j++) x = x + i;
    (*(int *)pnum_times)++;
  }

  return(NULL);
}

void TestSimpleMutex()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  pthread_t  thread1, thread2;
  r3 = 10;

  if (pthread_create(&thread1, NULL, do_one_thing_mutex, (void *)&r1) != 0)
    perror("pthread_create"), exit(1);

  if (pthread_create(&thread2, NULL, do_another_thing_mutex, (void *)&r2) != 0)
    perror("pthread_create"), exit(1);

  if (pthread_join(thread1, NULL) != 0)
    perror("pthread_join"), exit(1);

  if (pthread_join(thread2, NULL) != 0)
    perror("pthread_join"), exit(1);

  do_wrap_up(r1, r2);
  printf("r3 = %d\n", r3);
}
