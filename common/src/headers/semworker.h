#ifndef SEMWORKER_H
#define SEMWORKER_H

#include <string>

#include <semaphore.h>

class SemWorker
{
public:
    SemWorker(const std::string &, int);
    ~SemWorker();

    int getValue();
    int post();
    int tryWait();
    int wait();

private:
    // shared memory name for sem_unlink()
    const std::string semName;
    // address of semaphore
    sem_t *sem;
};

#endif  // SEMWORKER_H
