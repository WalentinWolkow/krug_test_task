#include "threads.h"

#include <iostream>

int main()
{
    ThreadOne *one = new ThreadOne();
    ThreadTwo *two = new ThreadTwo();

    std::cout << "\033[031mPress \'Enter\' to exit!\033[000m" << std::endl;
    std::cin.get();

    delete one;
    delete two;

    return 0;
}
