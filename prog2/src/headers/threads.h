#ifndef PROG2_THREADS_H
#define PROG2_THREADS_H

#include <threadworker.h>

class ShMemWorker;
class SemWorker;

class ThreadOne : public ThreadWorker
{
public:
    ThreadOne();
    ~ThreadOne();

    bool init();
    void loop();

private:
    ShMemWorker *shMem;
    SemWorker *sem[2];
};


class ThreadTwo : public ThreadWorker
{
public:
    ThreadTwo();
    ~ThreadTwo();

    bool init();
    void loop();

private:
    SemWorker *sem;
};

#endif  // PROG2_THREADS_H
