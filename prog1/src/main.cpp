#include <shmemworker.h>
#include <semworker.h>

#include <iostream>

int main()
{
    ShMemWorker memWorker("shMemTest");
    SemWorker semWorker("semTest", 0);

    std::cout << "Press \'q\' or \'Q\' to exit!\n" << std::endl;

    for ( ; ; )
    {
        std::string str;
        std::getline(std::cin, str);

        {
            size_t strSize = str.size();
            if (strSize == 0)
                continue;

            if (strSize == 1 && (str[0] == 'q' || str[0] == 'Q'))
                break;
        }

        std::cout << "Number of written bytes: " << memWorker.write(str) << std::endl;

        if (semWorker.getValue() == 0)
            semWorker.post();
    }

    return 0;
}
