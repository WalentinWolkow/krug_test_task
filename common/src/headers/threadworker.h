#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <pthread.h>

class ShMemWorker;
class SemWorker;

class ThreadWorker
{
public:
    typedef void (*pFunc)(void *);

    typedef struct StWorkers {
        ShMemWorker *shMem;
        SemWorker *sem1;
        SemWorker *sem2;

        StWorkers() : shMem(0), sem1(0), sem2(0) {};
    } *pWorkers;

    ThreadWorker(pFunc, pFunc);
    ~ThreadWorker();

private:
    int pipeFd[2];
    pthread_t threadId;
    pFunc mThreadLoopFunc;
    pWorkers workers;

    // Runner for thread function
    static void * threadFuncExec(void *);
};

#endif  // HOMETHREAD_H
