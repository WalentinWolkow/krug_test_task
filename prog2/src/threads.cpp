#include <threads.h>

#include <iostream>

bool ThreadOne::init()
{
    return true;
}

void ThreadOne::loop()
{
    std::cerr << '.';
}


bool ThreadTwo::loop()
{
    return true;
}

void ThreadTwo::loop()
{
    std::cerr << ';';
}
