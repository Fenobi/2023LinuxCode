#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void handler(int signo)
{
    pid_t ret = waitpid(-1, NULL, WNOHANG);
    while (ret > 0)
    {
        printf("wait child succsee: %d\n", ret);
    }
    printf("child is quit! %d\n", getpid());
}

void Count(int cnt)
{
    while (cnt)
    {
        printf("cnt: %d\n", cnt);
        fflush(stdout);
        cnt--;
        sleep(1);
    }
    printf("\n");
}
int main()
{ 
    // 显示的设置对SIGCHLD进行忽略
    signal(SIGCHLD, SIG_IGN);
    printf("我是父进程， %d,ppid: %d\n", getpid(), getppid());

    pid_t id = fork();
    if (id == 0)
    {
        printf("我是子进程， %d,ppid: %d,我要退出啦\n", getpid(), getppid());
        Count(5);
        exit(1);
    }
    while (true)
    {
        sleep(1);
    }
    return 0;
}

// void handler(int signo)
// {
//     cout << "\n" << "get a signo: " << signo << "正在处理中..." << endl;
//     sleep(2);
// }

// int main()
// {
//     struct sigaction act, oact;
//     act.sa_handler = handler;
//     act.sa_flags = 0;
//     act.sa_mask;
//     sigemptyset(&act.sa_mask);//当我们正在处理某一种信号的时候，我们也想顺便屏蔽其他信号，就可以添加到这个sa_mask中
//     sigaddset(&act.sa_mask, 3);
//     sigaction(SIGINT, &act, &oact);
//     while(true)
//     {
//         sleep(1);
//     }
//     return 0;
// }
