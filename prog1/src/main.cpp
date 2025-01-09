#include <shmemworker.h>
#include <semworker.h>

#include <iostream>

int main()
{
    ShMemWorker memWorker(SH_MEM_NAME);
    SemWorker semWorker(SH_MEM_SEM_NAME, 0);

    std::cout << "\033[031mEnter \'q\' or \'Q\' to exit!\033[000m\n" << std::endl;

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

        std::cout << "Number of written bytes: " << memWorker.write(str) << '\n' << std::endl;

        if (semWorker.getValue() == 0)
            semWorker.post();
    }

    return 0;
}
