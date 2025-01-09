#include <threadworker.h>
#include "threadfuncs.h"

#include <iostream>

int main()
{
    ThreadWorker *tw1 = new ThreadWorker(threadOneInitFunc, threadOneLoopFunc),
                 *tw2 = new ThreadWorker(threadTwoInitFunc, threadTwoLoopFunc);

    std::cout << "\033[031mPress \'Enter\' to exit!\033[000m" << std::endl;
    std::cin.get();

    delete tw1;
    delete tw2;

    return 0;
}
