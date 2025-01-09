#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <pthread.h>

class ThreadWorker
{
public:
    // param - pointer to thread function
    ThreadWorker(void (*)());
    ~ThreadWorker();

private:
    int pipeFd[2];
    pthread_t threadId;
    void (*mThreadFunc)(void);

    // Runner for thread function
    static void * threadFuncExec(void *);
};

#endif  // HOMETHREAD_H
