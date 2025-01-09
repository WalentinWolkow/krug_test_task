#include "shmemworker.h"

#include <iostream>

#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

ShMemWorker::ShMemWorker(const std::string &name) :
    shMemName(name),
    shMemFd(-1)
{
    // Create/open POSIX shared memory object
    shMemFd = shm_open(shMemName.data(), O_CREAT | O_RDWR, 0666);
    if (shMemFd == -1)
    {
        std::cerr << __PRETTY_FUNCTION__ << ", shm_open() error: " << strerror(errno) << '\n';

        return;
    }

    std::cout << __PRETTY_FUNCTION__ << ". Success: shared memory object created!" << std::endl;

    // Set size
    if (ftruncate(shMemFd, SH_MEM_BUF_SIZE) == -1)
    {
        std::cerr << __PRETTY_FUNCTION__ << ", ftruncate() error: " << strerror(errno) << '\n';
        close(shMemFd);

        shMemFd = -1;

        return;
    }

    // Attach to shared memory segment
    shMemBuf = (char *)mmap(0, SH_MEM_BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shMemFd, 0);
    if (shMemBuf == (char *)-1)
    {
        std::cerr << __PRETTY_FUNCTION__ << ", mmap() error: " << strerror(errno) << '\n';
        close(shMemFd);

        shMemFd = -1;

        return;
    }

    std::cout << __PRETTY_FUNCTION__ << ". Attaching address successful!" << std::endl;
}

ShMemWorker::~ShMemWorker()
{
    if (shMemFd == -1)
        return;

    if (close(shMemFd) == 0)
        std::cout << __PRETTY_FUNCTION__ << ". close() function successful!" << std::endl;
    else
        std::cerr << __PRETTY_FUNCTION__ << ", close() error: " << strerror(errno) << '\n';

    if (shm_unlink(shMemName.data()) == 0)
        std::cout << __PRETTY_FUNCTION__ << ". shm_unlink() function successful!" << std::endl;
    else
        std::cerr << __PRETTY_FUNCTION__ << ", shm_unlink() error: " << strerror(errno) << '\n';
}


size_t ShMemWorker::read(std::string &str)
{
    str.clear();

    if (shMemFd == -1)
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
    if (shMemFd == -1)
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
