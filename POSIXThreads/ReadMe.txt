========================================================================
    CONSOLE APPLICATION : POSIXThreads Project Overview
========================================================================

AppWizard has created this POSIXThreads application for you.

This file contains a summary of what you will find in each of the files that
make up your POSIXThreads application.


POSIXThreads.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

POSIXThreads.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

POSIXThreads.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named POSIXThreads.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes: pthread functions

int pthread_equal(pthread_t tid1, pthread_t tid2);  Returns: nonzero if equal, 0 otherwise
pthread_t pthread_self(void);                       Returns: the thread ID of the calling thread
int pthread_create(pthread_t *restrict tidp,
                   const pthread_attr_t *restrict attr,
                   void *(*start_rtn)(void *), void *restrict arg);
                                                    Returns: 0 if OK, error number on failure
void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr); Returns: 0 if OK, error number on failure
int pthread_cancel(pthread_t tid);                   Returns: 0 if OK, error number on failure
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);
int pthread_detach(pthread_t tid);                   Returns: 0 if OK, error number on failure


int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);    Both return: 0 if OK, error number on failure

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);     All return: 0 if OK, error number on failure

int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex,
                            const struct timespec *restrict tsptr);
                                                      Returns: 0 if OK, error number on failure

int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
                       const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock); Both return: 0 if OK, error number on failure

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);  All return: 0 if OK, error number on failure

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock); Both return: 0 if OK, error number on failure

int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock,
                               const struct timespec *restrict tsptr);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock,
                               const struct timespec *restrict tsptr);
                                                      Both return: 0 if OK, error number on failure
/////////////////////////////////////////////////////////////////////////////
