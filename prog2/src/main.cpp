//#include <threadworker.h>
#include <shmemworker.h>

#include <fstream>
#include <iostream>

//void threadOneFunc();
//void threadTwoFunc();

int main()
{
//    ThreadWorker tw1(threadOneFunc);
//    ThreadWorker tw2(threadTwoFunc);

    ShMemWorker shMemWorker;

    std::string str;
    shMemWorker.read(str);

    std::ofstream ofs("out.txt", std::ios_base::app);
    ofs << str << '\n';
    ofs.close();

    return 0;
}


/*void threadOneFunc()
{
    std::cerr << '.';
}

void threadTwoFunc()
{
    std::cerr << ';';
}*/
