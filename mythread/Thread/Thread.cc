#include "Thread.hpp"
#include <memory>
#include <unistd.h>
#include <vector>

// 当锁是全局的就不用初始化和销毁
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// 共享资源，火车票
int tickets = 10000;

// 多个线程交叉执行本质：就是让调度器尽可能的频繁发生线程调度与切换
// 线程一般在什么时候发生切换呢？切片时间到了，来了优先级更高的线程，线程等待的时候
// 线程是在什么时候检测上面的问题呢？从内核态返回用户态的时候，显示要对调度状态进行检测，如果可以，就直接发生进程切换

class ThreadData
{
public:
    ThreadData(const std::string &threadname, pthread_mutex_t *mutex_p) : _threadname(threadname), _mutex_p(mutex_p)
    {}
    ~ThreadData(){}
public:
    std::string _threadname;
    pthread_mutex_t *_mutex_p;
};

void *getTickets(void *args)
{
    //std::string username = static_cast<const char *>(args);
    ThreadData *td = static_cast<ThreadData *>(args);
    while (true)
    {
        // 加锁和解锁的过程是多个线程串行执行的，程序变慢了
        // 锁只规定互斥访问，没有规定必须让谁优先执行
        // 锁就是真正的让多个执行流进行竞争的结果
        pthread_mutex_lock(td->_mutex_p);
        if (tickets > 0)
        {
            usleep(100); // us
            std::cout << td->_threadname << " 正在进行抢票:" << tickets << std::endl;
            tickets--;
            pthread_mutex_unlock(td->_mutex_p);
        }
        else
        {
            pthread_mutex_unlock(td->_mutex_p);
            break;
        }
        // 模拟形成订单
        usleep(1000);
    }
    return nullptr;
}

int main()
{
#define NUM 4
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, nullptr);
    std::vector<pthread_t> tids(NUM);
    for (int i = 0; i < NUM;++i)
    {
        char buffer[64];
        snprintf(buffer, sizeof buffer, "thread %d", i + 1);
        ThreadData *td = new ThreadData(buffer,&lock);
        pthread_create(&tids[i], nullptr, getTickets, td);
    }

    for(const auto &tid:tids)
    {
        pthread_join(tid, nullptr);
    }

    pthread_mutex_destroy(&lock);

    // // std::unique_ptr<Thread> thread(new Thread(getTickets));
    // std::unique_ptr<Thread> thread1(new Thread(getTickets, (void *)"user1", 1));
    // std::unique_ptr<Thread> thread2(new Thread(getTickets, (void *)"user2", 2));
    // std::unique_ptr<Thread> thread3(new Thread(getTickets, (void *)"user3", 3));
    // std::unique_ptr<Thread> thread4(new Thread(getTickets, (void *)"user4", 4));
    // std::unique_ptr<Thread> thread5(new Thread(getTickets, (void *)"user5", 5));
    // std::unique_ptr<Thread> thread6(new Thread(getTickets, (void *)"user6", 6));
    // std::unique_ptr<Thread> thread7(new Thread(getTickets, (void *)"user7", 7));
    // // Thread *thread(new Thread(thrad_run, (void *)"logThrad", 3));
    // // thread->join();

    // thread1->join();
    // thread2->join();
    // thread3->join();
    // thread4->join();
    // thread5->join();
    // thread6->join();
    // thread7->join();
    return 0;
}
