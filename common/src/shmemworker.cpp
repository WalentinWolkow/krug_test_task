#include "shmemworker.h"

#include <iostream>

#include <sys/shm.h>
#include <string.h>

ShMemWorker::ShMemWorker() :
    shMemId(-1),
    shMemBuf((char *)-1),
    shMemSegSize(0)
{
    // Create shared memory segment with given key if not exist
    shMemId = shmget(SH_MEM_KEY, SH_MEM_BUF_SIZE, IPC_CREAT | 0600);
    if (shMemId == -1)
    {
        std::cerr << __PRETTY_FUNCTION__ << ", shmget() error!\n";

        return;
    }

    std::cout << __PRETTY_FUNCTION__ << ". Success: shared memory segment created!" << std::endl;

    // Attach to shared memory segment
    shMemBuf = (char *)shmat(shMemId, NULL, 0);
    if (shMemBuf == (char *)-1)
    {
        std::cerr << __PRETTY_FUNCTION__ << ", shmat() error!\n";

        return;
    }

    std::cout << __PRETTY_FUNCTION__ << ". Attaching address successful!" << std::endl;

    // Get size of shared memory segment
    struct shmid_ds ds;
    shmctl(shMemId, IPC_STAT, &ds);

    shMemSegSize = ds.shm_segsz;
    std::cout << __PRETTY_FUNCTION__ << ". Shared memory segment size: " << shMemSegSize << std::endl;
}

ShMemWorker::~ShMemWorker()
{
    if (shMemBuf != (char *)-1)
        shmdt(shMemBuf);

    if (shMemId == -1)
        return;

    // Remove shared memory segment if no more attachments
    struct shmid_ds ds;
    shmctl(shMemId, IPC_STAT, &ds);

    if (ds.shm_nattch == 0)
        shmctl(shMemId, IPC_RMID, NULL);
}


size_t ShMemWorker::read(std::string &str)
{
    str.clear();

    if (shMemId == -1 || shMemBuf == (char *)-1 || shMemSegSize == 0)
        return 0;

    for (size_t i = 0; i < SH_MEM_BUF_SIZE; ++i)
        if (*(shMemBuf + i) == 0)
        {
            str = std::string(shMemBuf);

            return str.size();
        }

    str = std::string(shMemBuf, SH_MEM_BUF_SIZE);

    return SH_MEM_BUF_SIZE;
}

size_t ShMemWorker::write(const std::string &str)
{
    if (shMemId == -1 || shMemBuf == (char *)-1 || shMemSegSize == 0)
        return 0;

    size_t strSize = str.size();

    if (strSize >= SH_MEM_BUF_SIZE)
    {
        strncpy(shMemBuf, str.data(), SH_MEM_BUF_SIZE);

        return SH_MEM_BUF_SIZE;
    }

    strcpy(shMemBuf, str.data());

    return strSize;
}
