#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
long long cnt = 0;
void handler(int signo)
{
    std::cout << "进程捕捉到了一个信号，信号编号是：" << signo << std::endl;
    exit(0);
}

static void Usage(const std::string &proc)
{
    std::cout << "\nUsage:" << proc << " pid signo\n"
              << std::endl;
    
}

void catchSig(int signo)
{
    std::cout << "cnt: " << cnt++ << std::endl;
    alarm(1);
    
}

int main(int argc, char *argv[])
{

    // // 4、软件条件
    // // 统计1S左右，计算机能够将数据打印多少次
    // signal(SIGALRM, catchSig);
    // alarm(1);
    // while (true)
    // {
    //     ++cnt;
    // }

    // 1、这里是signal函数的调用，并不是handler的调用
    // 仅仅是设置了对2号信号的捕捉方式，并不代表该方法被调用了
    // 一般这个方法不会执行，除非收到对应的信号
    // signal(2, handler);
    // while (true)
    // {
    //     std::cout << "我是一个进程：" << getpid() << std::endl;
    //     sleep(1);
    // }

    // 2、系统调用向目标进程发送信号
    // //kill()可以向任意进程发送任意信号
    // if (argc != 3)
    // {
    //     Usage(argv[0]);
    //     exit(1);
    // }

    // pid_t pid = atoi(argv[1]);
    // int signo = atoi(argv[2]);
    // int n = kill(pid, signo);
    // if (n != 0)
    // {
    //     perror("kill");
    // }

    // // raise() 给自己 发送 任意信号
    // int cnt = 0;
    // while (true)
    // {
    //     if (cnt <= 10)
    //     {
    //         printf("cnt:%d\n", cnt++);
    //         sleep(1);
    //         if (cnt >= 2)
    //         {
    //             raise(9);
    //         }
    //     }
    // }

    // // abort() 给自己 发送 指定的信号SIGABRT
    // int cnt = 0;
    // while (true)
    // {
    //     if (cnt <= 10)
    //     {
    //         printf("cnt:%d\n", cnt++);
    //         sleep(1);
    //         if (cnt >= 2)
    //         {
    //             abort();
    //         }
    //     }
    // }

    // 关于信号处理的行为的理解：有很多的情况，进程收到大部分的信号，默认处理动作都是终止进程
    // 信号的意义：信号的不同代表不同的事件，但是对事件发生之后的处理动作可以一样！

    //3、硬件异常产生
    // //信号产生，不一定非得用户显示的发送
    // while (true)
    // {
    //     std::cout << "我在运行中。。。 " << std::endl;
    //     sleep(1);
    //     int a = 10;
    //     // 如何证明？使用signal()替换SIGFPE
    //     // 收到信号，不一定会引起进程退出 -- 没有退出，有可能还会被调度
    //     // -- CPU内部的寄存器只有一份，但是寄存器中的内容，属于当前进程的上下文！
    //     // 而且自己没有能力修正这个问题
    //     // 当进程被切换的时候，就有无数次状态寄存器被保存和回复的过程
    //     // 所以每次恢复的时候，就让OS识别到了CPU内部的状态寄存器中的溢出标志位是1
    //     a /= 0;//当前进程会收到来自OS的信号(告知)SIGFPE
        
    // }
    
    //段错误SIGSEGV
    while(true)
    {
        std::cout << "我在运行中..." << std::endl;
        sleep(1);
        int *p = nullptr;
        *p = 12;// 野指针
    }

    

    return 0;
}
