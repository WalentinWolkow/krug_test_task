#include "threadworker.h"

#include <unistd.h>
#include <poll.h>

ThreadWorker::ThreadWorker() :
    threadId(0)
{
    if (pipe(pipeFd) == -1)
    {
        pipeFd[0] = pipeFd[1] = -1;

        return;
    }

    if (pthread_create(&threadId, NULL, exec, (void *)this) != 0)
    {
        close(pipeFd[0]);
        close(pipeFd[1]);

        pipeFd[0] = pipeFd[1] = -1;
        threadId = 0;
    }
}

ThreadWorker::~ThreadWorker()
{
    if (pipeFd[1] != -1)
    {
        write(pipeFd[1], "Q", 1);

        if (threadId != 0)
            pthread_join(threadId, NULL);

        close(pipeFd[1]);
    }

    if (pipeFd[0] != -1)
        close(pipeFd[0]);
}


void * ThreadWorker::exec(void *data)
{
    ThreadWorker *instance = (ThreadWorker *)data;

    if (!instance->init())
        return NULL;

    struct pollfd pollFd;
    pollFd.fd = instance->pipeFd[0];
    pollFd.events = POLLIN;

    for ( ; ; )
    {
        instance->loop();

        int pollRes = poll(&pollFd, 1, 1000);
        if (pollRes == 0)
            continue;

        if (pollRes < 0)
            return NULL;

        if (pollFd.revents & POLLIN)
        {
            char c;
            read(pollFd.fd, &c, sizeof(char));
            if (c == 'Q' || c == 'q')
                break;
        }
    }

    return NULL;
}
