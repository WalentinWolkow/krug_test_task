#include <shmemworker.h>

#include <iostream>

int main()
{
    ShMemWorker memWorker;

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
    }

    return 0;
}
