#include <iostream>
#include <pthread.h>
#include <cassert>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

class ThreadData
{
public:
    int num;
    pthread_t tid;
    char namebuffer[64];
};

class ThreadReturn
{
public:
    int exit_code;
    int exit_result;
};

//新线程
//1.thread_routine，现在是被10个线程执行，处于重入状态
//2.该函数是可重入函数
//3.在函数内定义的变量，都叫做局部变量，具有临时性 --在多线程下依旧适用 -- 每个线程都有自己独立的栈结构

void *thread_routine(void* args)
{
    sleep(1);
    ThreadData *td = static_cast<ThreadData * > (args); // 安全的进行强制类型转换
    int cnt = 10;
    while (cnt)
    {
        cout << "我是新线程，我正在运行！name:" << td->namebuffer << " cnt: " << cnt-- << endl;//bug
        sleep(1);
        //exit(0);//不能用来终止线程，exit是终止进程的
        //pthread_exit((void*)td->num);//终止线程 
        // //一个线程如果出现异常，会影响其他线程（健壮性或者鲁棒性较差）
        // //为什么？进程信号，信号是整体发给进程的
        // int *p = nullptr;
        // *p = 0;
    }
    // 线程如何终止
     delete td;
    // return nullptr;//return终止
    // return (void *)td->num;
     pthread_exit((void*)100);//既然假的地址，整数都能被外部拿到，那么如果返回的是，堆空间的地址呢？对象的地址呢？
    // ThreadReturn *tr = new ThreadReturn();
    // tr->exit_code = 1;
    // tr->exit_result = 'f';

    // ThreadReturn tr;//在栈上开辟的空间 return &tr

    // return (void *)tr;//右值
}

int main()
{
    //1.创建一批进程
    vector<ThreadData*> threads;
#define NUM 10
    for (int i = 0; i < NUM;++i)
    {
        ThreadData *td = new ThreadData();
        snprintf(td->namebuffer, sizeof td->namebuffer, "%s:%d", "thread", i+1);
        pthread_create(&td->tid, nullptr, thread_routine, td);
        td->num = i;
        threads.push_back(td);

        // pthread_t tid;
        // char namebuffer[64];
        // snprintf(namebuffer, sizeof namebuffer, "%s:%d", "thread", i);
        // pthread_create(&tid, nullptr, thread_routine, namebuffer);

        // pthread_create(&tid, nullptr, thread_routine, (void *)"thread one");
    }

    for(auto &iter:threads)
    {
        std::cout << "create thread: " << iter->namebuffer << ":" << iter->tid << " sucess" << endl;
    }
    // 线程是可以用cancel取消的。注意！：线程要被取消，前提是这个线程就已经跑起来了
    // 线程如果是被取消的，退出码：-1
    // PTHREAD_CANCELED;
    sleep(5);
    for (int i = 0; i < threads.size()/2;++i)
    {
        pthread_cancel(threads[i]->tid);
        cout << "pthread_cancel : " << threads[i]->namebuffer << " success " << endl;
    }

    for (auto &iter : threads)
    {
        int *ret = nullptr;
        // 线程等待
        // 在线程退出的时候，为什么见不到对应的退出信号呢？？线程出异常，收到信号，整个进程都会退出
        //pthread_join:默认就认为函数会调用成功，不考虑异常问题，异常问题是进程考虑的问题
        int n = pthread_join(iter->tid, (void**)&ret);//(void**)
        assert(n == 0);
        cout << "join : " << iter->namebuffer << " success code: " << (long long)ret << endl;
        delete iter;
    }

    while(true)
    {
        cout << "我是主线程，我正在运行！name:main thread." << endl;
        sleep(1);
    }

    // pthread_t tid;
    // int n = pthread_create(&tid, nullptr, thread_routine, (void*)"thread one");
    // assert(0 == n);
    // (void)n;
    // //主线程
    // while(true)
    // {
    //     // 地址->?
    //     char tidbuffer[64];                                                                                                                                                
    //     snprintf(tidbuffer, sizeof tidbuffer, "0x%x", tid);
    //     cout << "我是主线程，我正在运行！tid:" << tidbuffer << endl;
    //     sleep(1);
    // }
    return 0;
}