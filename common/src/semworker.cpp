#include "semworker.h"

#include <iostream>

#include <fcntl.h>
#include <string.h>

SemWorker::SemWorker(const std::string &name, int value) :
    semName(name),
    sem(SEM_FAILED)
{
    // Create/open POSIX semaphore
    sem = sem_open(semName.data(), O_CREAT, 0600, value);
    if (sem == SEM_FAILED)
        std::cerr << __PRETTY_FUNCTION__ << ", sem_open() error: " << strerror(errno) << '\n';
    else
        std::cout << __PRETTY_FUNCTION__ << ". Success: semaphore created!" << std::endl;

    std::cout << "SEM_FAILED = " << SEM_FAILED << std::endl;
}

SemWorker::~SemWorker()
{
    if (sem == SEM_FAILED)
        return;

    // Close semaphore
    if (sem_close(sem) == 0)
        std::cout << __PRETTY_FUNCTION__ << ". sem_close() function successful!" << std::endl;
    else
        std::cerr << __PRETTY_FUNCTION__ << ", sem_close() error: " << strerror(errno) << '\n';

    // Remove semaphore object
    if (sem_unlink(semName.data()) == 0)
        std::cout << __PRETTY_FUNCTION__ << ". sem_unlink() function successful!" << std::endl;
    else
        std::cerr << __PRETTY_FUNCTION__ << ", sem_unlink() error: " << strerror(errno) << '\n';
}


int SemWorker::getValue()
{
    if (sem == SEM_FAILED)
        return -1;

    int val;
    if (sem_getvalue(sem, &val) == -1)
    {
        std::cerr << __PRETTY_FUNCTION__ << ", sem_getval() error: " << strerror(errno) << '\n';

        return -1;
    }

    return val;
}

int SemWorker::post()
{
    if (sem == SEM_FAILED)
        return -1;

    int res = sem_post(sem);
    if (res == 0)
        std::cout << __PRETTY_FUNCTION__ << ". sem_post() function successful!" << std::endl;
    else
        std::cerr << __PRETTY_FUNCTION__ << ", sem_post() error: " << strerror(errno) << '\n';

    return res;
}
