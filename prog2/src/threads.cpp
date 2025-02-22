#include <threads.h>
#include <shmemworker.h>
#include <semworker.h>

#include <vector>
#include <fstream>

#include <string.h>

#define FILE_SEM_NAME   "FileSem"
#define TEST_FILE_NAME  "test.txt"
#define TMP_FILE_NAME   "tmp.txt"

#define MAX_STR_NUM     128


// Thread one
ThreadOne::ThreadOne() :
    shMem(NULL),
    sem{NULL, NULL}
{
}

ThreadOne::~ThreadOne()
{
    if (shMem != NULL)
        delete shMem;

    for (int i = 0; i < 2; ++i)
        if (sem[i] != NULL)
            delete sem[i];
}


bool ThreadOne::init()
{
    shMem = new ShMemWorker(SH_MEM_NAME);
    sem[0] = new SemWorker(SH_MEM_SEM_NAME, 0);
    sem[1] = new SemWorker(FILE_SEM_NAME, 1);

    return true;
}

void ThreadOne::loop()
{
    static std::vector<std::string> vecBuf;

    if (sem[0]->tryWait() == 0)
    {
        std::string str;
        shMem->read(str);

        vecBuf.push_back(str);
    }

    if (vecBuf.empty())
        return;

    if (sem[1]->tryWait() != 0)
        return;

    std::ofstream ofs(TEST_FILE_NAME, std::ios_base::app);
    for (std::vector<std::string>::iterator it = vecBuf.begin(), itEnd = vecBuf.end(); it != itEnd; ++it)
        ofs << *it << '\n';

    vecBuf.clear();

    sem[1]->post();
}



// Thread two
ThreadTwo::ThreadTwo() :
    sem(NULL)
{
}

ThreadTwo::~ThreadTwo()
{
    if (sem != NULL)
        delete sem;
}


bool ThreadTwo::init()
{
    sem = new SemWorker(FILE_SEM_NAME, 1);

    return true;
}

void ThreadTwo::loop()
{
    if (sem->tryWait() != 0)
        return;

    // Sorting jobs begin
    {
        static std::streampos lastSortPos = 0;

        std::ifstream ifs(TEST_FILE_NAME);
        ifs.seekg(0, std::ios_base::end);

        std::streampos fileLength = ifs.tellg();
        if (lastSortPos >= fileLength)
        {
            ifs.close();
            sem->post();

            return;
        }


        std::vector<std::string> vec;
        for (ifs.seekg(lastSortPos); ifs.tellg() < fileLength; )
        {
            std::string str;
            std::getline(ifs, str);

            vec.push_back(str);
        }

        std::vector<std::string> vecNewSort;
        for (std::vector<std::string>::iterator it1 = vec.begin(); vec.size() > 1; it1 = vec.begin())
        {
            for (std::vector<std::string>::iterator it2 = it1 + 1, itEnd = vec.end(); it2 != itEnd; ++it2)
                if (strcmp(it1->data(), it2->data()) > 0)
                    it1 = it2;

            vecNewSort.push_back(*it1);
            vec.erase(it1);
        }
        vecNewSort.insert(vecNewSort.end(), vec.begin(), vec.end());

        std::ofstream ofs(TMP_FILE_NAME);
        for (ifs.seekg(0); ifs.tellg() < lastSortPos; )
        {
            vec.clear();
            for (int i = 0; i < MAX_STR_NUM && ifs.tellg() < lastSortPos; ++i)
            {
                std::string str;
                std::getline(ifs, str);

                vec.push_back(str);
            }

            for ( ; !(vecNewSort.empty() || vec.empty()); )
            {
                std::vector<std::string>::iterator itNewSort = vecNewSort.begin(), it = vec.begin();
                if (strcmp(itNewSort->data(), it->data()) < 0)
                {
                    ofs << *itNewSort << '\n';
                    vecNewSort.erase(itNewSort);
                }
                else
                {
                    ofs << *it << '\n';
                    vec.erase(it);
                }
            }

            if (vecNewSort.empty())
                for (std::vector<std::string>::iterator it = vec.begin(), itEnd = vec.end(); it != itEnd; ++it)
                    ofs << *it << '\n';
        }

        if (!vecNewSort.empty())
            for (std::vector<std::string>::iterator it = vecNewSort.begin(), itEnd = vecNewSort.end(); it != itEnd; ++it)
                ofs << *it << '\n';

        ifs.close();
        ofs.close();

        lastSortPos = fileLength;

        rename(TMP_FILE_NAME, TEST_FILE_NAME);
    }
    // End of sorting jobs

    sem->post();
}
