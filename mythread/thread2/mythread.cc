#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <pthread.h>
#include <cstdio>

//添加__thread，可以将一个内置类型设置为线程局部储存
__thread int g_val = 100;

std::string changeId(const pthread_t &thread_id)
{
    char tid[128];
    snprintf(tid, sizeof tid, "0x%x", thread_id);
    return tid;
}

void* start_routine(void *args)
{
    std::string thraedname = static_cast<const char *>(args);
    //pthread_detach(pthread_self()); //设置自己为分离状态

    int cnt = 5;
    while (cnt--)
    {
        std::cout << thraedname << " running ... : " << changeId(pthread_self()) << " g_val: " << g_val << " &g_val " << &g_val << std::endl;
        sleep(1);
        g_val++;
    }
    return nullptr;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, start_routine, (void *)"thread 1");
    std::string main_id = changeId(pthread_self());
    pthread_detach(tid);

    //std::cout << " main thread running ... new thread id: " << changeId(tid) << " main id: " << main_id << std::endl;

    // // 一个线程默认是joinable的，如果设置了分离状态，不能够进行等待
    // int n = pthread_join(tid, nullptr);
    // std::cout << "result: " << n << ":" << strerror(n) << std::endl;
    while(true)
    {
        std::cout << "main thread running ... new thread id: " << changeId(tid) \
            << " main id: " << main_id << " g_val: " << g_val << " &g_val " << &g_val << std::endl;
        sleep(1);
    }

    return 0;
}