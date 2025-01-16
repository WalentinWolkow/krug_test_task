#ifndef PROG2_THREADS_H
#define PROG2_THREADS_H

#include <threadworker.h>

class ThreadOne : public ThreadWorker
{
public:
    ThreadOne() {}
    ~ThreadOne() {}

    bool init() { return true; }
    void loop();
};


class ThreadTwo : public ThreadWorker
{
public:
    ThreadTwo() {}
    ~ThreadTwo() {}

    bool init() { return true; }
    void loop();
};

#endif  // PROG2_THREAS_H
