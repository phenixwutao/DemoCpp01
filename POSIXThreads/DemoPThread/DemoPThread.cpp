#include "StdAfx.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <process.h>
#include <windows.h>
#include <time.h>

#include <iostream>
#include <string>

#include "DemoPThread.h"

#define NUM_THREADS     5
#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)

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

  if (tmp) delete tmp;

  if (err == 0)
    printf("mutex locked again!\n");
  else
    printf("can't lock mutex again: %d\n", (err));
}

void maketimeout(struct timespec *tsp, long minutes)
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);

  /* get the current time */
  timespec_get(tsp, TIME_UTC);

  struct tm tmp;
  time_t rawtime;
  time(&rawtime);
  auto errNum = localtime_s(&tmp, &rawtime);
  char buf[64] {};
  strftime(buf, sizeof(buf), "%r", &tmp);
  printf("current time is %s\n", buf);

  tsp->tv_sec += minutes * 60;

  rawtime = tsp->tv_sec;
  errNum = localtime_s(&tmp, &rawtime);
  strftime(buf, sizeof(buf), "%r", &tmp);
  printf("makeout time is %s\n", buf);
}

void TestTimeMakeOuttime()
{
  timespec tspec;
  maketimeout(&tspec, 10); // make a time 10 minutes ahead
}

//----------------------- demo mutex lock ----------------------
struct foo1
{
  int             f_count;
  pthread_mutex_t f_lock;
  int             f_id;
};

foo1* foo1_alloc(int id) /* allocate the object */
{
  foo1 *fp = new foo1;;

  if (fp != nullptr) {
    fp->f_count = 1;
    fp->f_id = id;

    // initialise mutex with default attributes
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
    {
      delete (fp);
      return(NULL);
    }
    /* ... continue initialization ... */
  }
  return(fp);
}

void foo1_hold(foo1 **fptr) /* add a reference to the object */
{
  foo1* fp = *fptr;
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

void foo1_release(foo1 **fptr) /* release a reference to the object */
{
  foo1* fp = *fptr;
  pthread_mutex_lock(&fp->f_lock);
  if (--fp->f_count == 0)  /* last reference */
  {
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_destroy(&fp->f_lock);
    delete fp;
    *fptr = NULL;
  }
  else
  {
    pthread_mutex_unlock(&fp->f_lock);
  }
}

void TestMutexLockUnlock()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  foo1* foo_ibj = foo1_alloc(10);
  printf("foo1_alloc count %d\n", foo_ibj->f_count);

  while (foo_ibj != nullptr && foo_ibj->f_count < 10)
  {
    foo1_hold(&foo_ibj);
    printf("foo1_alloc count %d\n", foo_ibj->f_count);
  }

  while (foo_ibj != nullptr)
  {
    if (foo_ibj != nullptr)
      printf("foo1_release count %d\n", foo_ibj->f_count);

    foo1_release(&foo_ibj);
  }
}


struct foo2 *fh[NHASH];

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo2 {
  int             f_count;
  pthread_mutex_t f_lock;
  int             f_id;
  struct foo2     *f_next; /* protected by hashlock */
                          /* ... more stuff here ... */
};

foo2* foo_alloc2(int id) /* allocate the object */
{
  foo2	*fp = new foo2;

  if (fp != nullptr)
  {
    fp->f_count = 1;
    fp->f_id = id;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
    {
      delete fp;
      return nullptr;
    }
    int idx = HASH(id);
    pthread_mutex_lock(&hashlock);
    fp->f_next = fh[idx];
    fh[idx] = fp;
    pthread_mutex_lock(&fp->f_lock);

    pthread_mutex_unlock(&hashlock);
    pthread_mutex_unlock(&fp->f_lock);
  }
  return (fp);
}

void foo_hold2(foo2 **fptr) /* add a reference to the object */
{
  foo2 *fp = *fptr;
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

foo2 *foo_find2(int id) /* find an existing object */
{
  foo2 *fp;

  pthread_mutex_lock(&hashlock);
  for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next)
  {
    if (fp->f_id == id) {
      foo_hold2(&fp);
      break;
    }
  }
  pthread_mutex_unlock(&hashlock);
  return fp;
}

void foo_release2(foo2 **fptr) /* release a reference to the object */
{
  foo2* fp = *fptr;
  foo2* tfp = nullptr;

  pthread_mutex_lock(&fp->f_lock);
  if (fp->f_count == 1)  /* last reference */
  {
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_lock(&hashlock);
    pthread_mutex_lock(&fp->f_lock);
    /* need to recheck the condition */
    if (fp->f_count != 1) {
      fp->f_count--;
      pthread_mutex_unlock(&fp->f_lock);
      pthread_mutex_unlock(&hashlock);
      return;
    }
    /* remove from list */
    int idx = HASH(fp->f_id);
    tfp = fh[idx];
    if (tfp == fp)
    {
      fh[idx] = fp->f_next;
    }
    else
    {
      while (tfp->f_next != fp)
        tfp = tfp->f_next;
      tfp->f_next = fp->f_next;
    }
    pthread_mutex_unlock(&hashlock);
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_destroy(&fp->f_lock);
    delete fp;
  }
  else
  {
    fp->f_count--;
    pthread_mutex_unlock(&fp->f_lock);
  }
}

void TestMutexLockUnlockLinkedStruct()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  foo2* fp_obj = foo_alloc2(3);
  foo_hold2(&fp_obj);
  foo_release2(&fp_obj);
}

void cleanup(void *arg)
{
  printf("cleanup: %s\n", (char *)arg);
}

void* thr_cleanup_fn1(void *arg)
{
  printf("thread 1 start\n");
  pthread_cleanup_push(cleanup, "thread 1 first handler");
  pthread_cleanup_push(cleanup, "thread 1 second handler");
  printf("thread 1 push complete\n");
  if (arg)
    return((void *)1); // will not call cleanup function

  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return((void *)1);
}

void * thr_cleanup_fn2(void *arg)
{
  printf("thread 2 start\n");
  /******************************************************************************************
  * pthread_cleanup_push schedules the cleanup functions. The functions are known as thread 
  * cleanup handlers. More than one cleanup handler can be established for a thread. 
  * The handlers are recorded in a stack, which means that they are executed in the reverse
  * order from that with which they were registered.
  *******************************************************************************************/
  pthread_cleanup_push(cleanup, "thread 2 first handler");
  pthread_cleanup_push(cleanup, "thread 2 second handler");
  printf("thread 2 push complete\n");
  if (arg)
    pthread_exit((void *)2); // trigger the cleanup functions to be called


  // argument is set to 0, the cleanup function is not called.
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  pthread_exit((void *)2);
  return nullptr;
}

void TestPthreadCleanupHandlers()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  pthread_t	tid1, tid2;
  void *retval = nullptr;

  int err = pthread_create(&tid1, NULL, thr_cleanup_fn1, (void *)1);
  if (err != 0)
    printf("can't create thread 1: err %d\n", err);

  err = pthread_create(&tid2, NULL, thr_cleanup_fn2, (void *)1);
  if (err != 0)
    printf("can't create thread 2: err %d\n", err);

  err = pthread_join(tid1, &retval);
  if (err != 0)
    printf("can't join with thread 1: err %d\n", err);
  printf("thread 1 exit code %ld\n", (long)retval);

  err = pthread_join(tid2, &retval);
  if (err != 0)
    printf("can't join with thread 2: err %d\n", err);
  printf("thread 2 exit code %ld\n", (long)retval);
}

/*------------------------- TestReaderWriterLock ---------------------------*/
struct job {
  struct job *j_next;
  struct job *j_prev;
  pthread_t   j_id;   /* tells which thread handles this job */
                      /* ... more stuff here ... */
};

struct queue {
  struct job      *q_head;
  struct job      *q_tail;
  pthread_rwlock_t q_lock;
};

/*
* Initialize a queue.
*/
int queue_init(queue *qp)
{
  qp->q_head = NULL;
  qp->q_tail = NULL;
  int err = pthread_rwlock_init(&qp->q_lock, NULL);
  if (err != 0)
    return(err);
  /* ... continue initialization ... */
  return (0);
}

/*
* Insert a job at the head of the queue.
*/
void job_insert(queue *qp, job *jp)
{
  pthread_rwlock_wrlock(&qp->q_lock);
  jp->j_next = qp->q_head;
  jp->j_prev = NULL;
  if (qp->q_head != NULL)
    qp->q_head->j_prev = jp;
  else
    qp->q_tail = jp;	/* list was empty */
  qp->q_head = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

/*
* Append a job on the tail of the queue.
*/
void job_append(queue *qp, job *jp)
{
  pthread_rwlock_wrlock(&qp->q_lock);
  jp->j_next = NULL;
  jp->j_prev = qp->q_tail;
  if (qp->q_tail != NULL)
    qp->q_tail->j_next = jp;
  else
    qp->q_head = jp;	/* list was empty */
  qp->q_tail = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

/*
* Remove the given job from a queue.
*/
void job_remove(queue *qp, job *jp)
{
  pthread_rwlock_wrlock(&qp->q_lock);
  if (jp == qp->q_head)
  {
    qp->q_head = jp->j_next;
    if (qp->q_tail == jp)
      qp->q_tail = NULL;
    else
      jp->j_next->j_prev = jp->j_prev;
  }
  else if (jp == qp->q_tail)
  {
    qp->q_tail = jp->j_prev;
    jp->j_prev->j_next = jp->j_next;
  }
  else
  {
    jp->j_prev->j_next = jp->j_next;
    jp->j_next->j_prev = jp->j_prev;
  }
  pthread_rwlock_unlock(&qp->q_lock);
}

/*
* Find a job for the given thread ID.
*/
job* job_find(queue *qp, pthread_t id)
{
  job *jp;

  if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
    return(NULL);

  for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
    if (pthread_equal(jp->j_id, id))
    {
      printf("find a match: %llu %llu\n", jp->j_id, id);
      break;
    }

  pthread_rwlock_unlock(&qp->q_lock);
  return(jp);
}

void* job_func(void* arg)
{
  printf("                               exec job %u\n", (int)arg);
  return nullptr;
}
void TestReaderWriterLock()
{
  printf("-------------------------- Pass %d -> '%s'\n", iPass++, __func__);
  job job1;
  job job2;
  job job3;
  job job4;
  job job5;
  job job6;

  int argval = 1;
  auto err = pthread_create(&(job1.j_id), NULL, job_func,(void*)argval++);
  if (err != 0)
    printf("job%d thread failed\n", argval);

  err = pthread_create(&(job2.j_id), NULL, job_func, (void*)argval++);
  if (err != 0)
    printf("job%d thread failed\n", argval);

  err = pthread_create(&(job3.j_id), NULL, job_func, (void*)argval++);
  if (err != 0)
    printf("job%d thread failed\n", argval);

  err = pthread_create(&(job4.j_id), NULL, job_func, (void*)argval++);
  if (err != 0)
    printf("job%d thread failed\n", argval);

  err = pthread_create(&(job5.j_id), NULL, job_func, (void*)argval++);
  if (err != 0)
    printf("job%d thread failed\n", argval);

  err = pthread_create(&(job6.j_id), NULL, job_func, (void*)argval++);
  if (err != 0)
    printf("job%d thread failed\n", argval);

  queue job_queue;
  queue_init(&job_queue);

  job_insert(&job_queue, &job1);
  job_insert(&job_queue, &job2);
  job_insert(&job_queue, &job3);
  job_append(&job_queue, &job4);
  job_append(&job_queue, &job5);
  job_append(&job_queue, &job6);

  auto findjob = job_find(&job_queue, job4.j_id);
  if (findjob != nullptr)
    printf("find job thread id: %u  %llu\n", findjob->j_id.x, findjob->j_id);

  pthread_join(job1.j_id, NULL);
  pthread_join(job2.j_id, NULL);
  pthread_join(job3.j_id, NULL);
  pthread_join(job4.j_id, NULL);
  pthread_join(job5.j_id, NULL);
  pthread_join(job6.j_id, NULL);

}


struct msg {
  msg(std::string ms) : strMessage(ms) {}
  struct msg *m_next;
  std::string strMessage;
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg()
{
  msg *mp;

  for (;;) {
    pthread_mutex_lock(&qlock);
    while (workq == NULL)
      pthread_cond_wait(&qready, &qlock);

    mp = workq;
    mp->strMessage = workq->strMessage;
    printf("process message: %s\n", mp->strMessage.c_str());

    workq = mp->m_next;
    workq->strMessage = mp->m_next->strMessage;

    pthread_mutex_unlock(&qlock);
    /* now process the message mp */
  }
}

void enqueue_msg(msg *mp)
{
  pthread_mutex_lock(&qlock);
  mp->m_next = workq;
  mp->m_next->strMessage = workq->strMessage;

  workq = mp;
  workq->strMessage = mp->strMessage;

  pthread_cond_signal(&qready);
  pthread_mutex_unlock(&qlock);
}

void TestConditionVariables()
{
}
