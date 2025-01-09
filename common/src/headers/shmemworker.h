#ifndef SHMEMWORKER_H
#define SHMEMWORKER_H

#include <string>

#define SH_MEM_KEY      128
#define SH_MEM_BUF_SIZE 4096

class ShMemWorker
{
public:
    ShMemWorker();
    ~ShMemWorker();

    // Read data from shared memory
    // param - string to read data
    // Return value - number of bytes read from shared memory
    size_t read(std::string &);

    // Write data to shared memory
    // param - string to write
    // Return value - number of bytes written to shared memory
    size_t write(const std::string &);

private:
    // Shared memory ID
    int shMemId;
    // Pointer to shared memory buffer
    char *shMemBuf;
    // Real size of shared memory buffer
    size_t shMemSegSize;
};

#endif  // SHMEMWORKER_H
