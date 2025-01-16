#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <pthread.h>

class ThreadWorker
{
public:
    ThreadWorker();
    virtual ~ThreadWorker();

    // Thread functions
    virtual bool init() = 0;
    virtual void loop() = 0;

private:
    int pipeFd[2];
    pthread_t threadId;

    // Runner for thread functions
    static void * exec(void *);
};

#endif  // HOMETHREAD_H
