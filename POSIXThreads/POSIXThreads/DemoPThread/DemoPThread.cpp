#include "StdAfx.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <process.h>
#include <windows.h>
#include <time.h>
#include <iostream>

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

static pthread_once_t welcome_once_block = PTHREAD_ONCE_INIT;

void welcome(void)
{
  printf("welcome: Welcome\n");
}

void *identify_yourself(void *arg)
{
  int *pid = (int *)arg;
  int rtn = pthread_once(&welcome_once_block, welcome); // thread initialise once only
  if (rtn!= 0)
  {
    fprintf(stderr, "pthread_once failed with %d", rtn);
    pthread_exit((void *)NULL);
  }
  printf("identify_yourself: Hi, I'm thread # %d\n", *pid);
  return(NULL);
}

void TestThreadOnceOnly()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  int rtn = 0;
  pthread_t threads[NUM_THREADS];

  int* id_arg = (int *)malloc(NUM_THREADS * sizeof(int));

  for (int thread_num = 0; thread_num < NUM_THREADS; (thread_num)++)
  {
    id_arg[thread_num] = thread_num;

    if ((rtn = pthread_create(&threads[thread_num], NULL,
                              identify_yourself,
                             (void *) &(id_arg[thread_num]))) != 0)
    {
      fprintf(stderr, "pthread_create failed with %d", rtn);
      exit(1);
    }
  }

  for (int thread_num = 0; thread_num < NUM_THREADS; thread_num++)
  {
    pthread_join(threads[thread_num], NULL);
    printf("joined to thread %d\n", thread_num);
  }
  printf("Goodbye %s\n", __func__);
}


pthread_t ntid;

void PrintThreadIDs(const char *s)
{
  pid_t pid = _getpid();
  pthread_t tid = pthread_self();
  printf("%s process id %u thread id %lu (0x%lx)\n", s, (int)pid,
    (unsigned long)&tid, (unsigned long)&tid);
}

void* thr_fn(void *arg)
{
  PrintThreadIDs("new thread: ");
  return nullptr;
}


void TestThreadIDs()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  int err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0)
    perror("can't create thread");

  PrintThreadIDs("main thread:");
  pthread_join(ntid, NULL);

  pthread_t t1;
  pthread_t t2;
  pthread_create(&t1, NULL, thr_fn, NULL);
  pthread_create(&t2, NULL, thr_fn, NULL);
  int wSameID = pthread_equal(t1, t2); // threads t1 and t2 are not same
  printf("Same thread ID %s\n", wSameID !=0 ? "Same":"Not same");

  pthread_t idCurrent = pthread_self();
  wSameID = pthread_equal(t1, idCurrent); // threads t1 and main are not same
  printf("Same thread ID %s\n", wSameID != 0 ? "Same" : "Not same");

  pthread_t idCurrent2 = pthread_self();
  wSameID = pthread_equal(idCurrent2, idCurrent); // threads main and main are same
  printf("Same thread ID %s\n", wSameID != 0 ? "Same" : "Not same");
  return;
}

void * thr_fn1(void *arg)
{
  printf("thread 1 returning\n");
  return((void *)1);
}

void * thr_fn2(void *arg)
{
  printf("thread 2 exiting\n");
  pthread_exit((void *)2);
  return nullptr;
}

void TestThreadExitStatus()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  pthread_t	tid1 {}, tid2 {};
  void* threadExitStatus = nullptr;

  int err = pthread_create(&tid1, NULL, thr_fn1, NULL);
  if (err != 0)
    perror("can't create thread 1");

  err = pthread_create(&tid2, NULL, thr_fn2, NULL);
  if (err != 0)
    perror("can't create thread 2");

  err = pthread_join(tid1, &threadExitStatus); // get return value
  if (err != 0)
    perror("can't join with thread 1");
  
  printf("thread 1 exit code %ld\n", (long)threadExitStatus);

  err = pthread_join(tid2, &threadExitStatus); // get pthread_exit value
  if (err != 0)
    perror("can't join with thread 2");

  printf("thread 2 exit code %ld\n", (long)threadExitStatus);
}

void TestTimedMutexLock()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  struct timespec tout {};
  struct tm *tmp = new tm;
  char buf[64] {};
  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&lock);
  printf("mutex is locked\n");

  time_t rawtime;
  time(&rawtime);

  // tmp = localtime(&rawtime);  // depreciated old function
  //                        output  input
  auto errNum = localtime_s(tmp, &rawtime);

  strftime(buf, sizeof(buf), "%r", tmp);
  printf("current time is %s\n", buf);

  /* 5 seconds from now */
  /* caution: this could lead to deadlock */
  tout.tv_sec = rawtime + 5;

  /********************************************************************************************
  * The pthread_mutex_timedlock() function shall lock the mutex object referenced by mutex. 
  * If the mutex is already locked, the calling thread shall block until the mutex becomes 
  * available as in the pthread_mutex_lock() function. If the mutex cannot be locked without 
  * waiting for another thread to unlock the mutex, this wait shall be terminated when the 
  * specified timeout expires.
  */
  int err = pthread_mutex_timedlock(&lock, &tout);
  
  if (err = ETIMEDOUT)
    printf("Timed out: The mutex could not be locked before the specified timeout expired.\n");

  time(&tout.tv_sec);
  errNum = localtime_s(tmp, &tout.tv_sec);

  strftime(buf, sizeof(buf), "%r", tmp);
  printf("the time is now %s\n", buf);

  if (err == 0)
    printf("mutex locked again!\n");
  else
    printf("can't lock mutex again: %d\n", (err));
}
