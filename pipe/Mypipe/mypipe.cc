#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cassert>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

// 父进程进行读取，子进程写入
int main()
{
    // 第一步：创建管道文件，打开读写端
    int fds[2];
    int n = pipe(fds);
    assert(n == 0);

    // 第二步：fork
    pid_t id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        // 子进程进行写入
        close(fds[0]);
        // 子进程的通信代码
        const char *s = "我是子进程，我正在给你发消息";
        int cnt = 0;
        while (true)
        {
            ++cnt;
            char buffer[1024]; // 只有子进程能看到
            snprintf(buffer, sizeof buffer, "child->parent say:%s[%d][%d]", s, cnt, getpid());
            write(fds[1], buffer, strlen(buffer));
            sleep(1);//细节： 每隔一秒写一次
        }

        // 子进程
        close(fds[1]);
        exit(0);
    }
    // 父进程进行读取
    close(fds[1]);
    // 父进程的通信代码
    while(true)
    {
        char buffer[1024];
        // ssize_t:long int
        // 如果管道中没有了数据，读端在读，默认会直接阻塞当前正在读取的进程
        ssize_t s = read(fds[0], buffer, sizeof(buffer) - 1);
        if(s > 0)
        {
            buffer[s] = 0;// 在下标最后一个位置置零，加\0
            cout << "Get Message# " << buffer << " | my pid: " << getpid() << endl;
        }
        else if(s == 0)
        {
            //读到文件结尾
            cout << "read: " << s << endl;
            break;
        }

        // 细节：父进程没有进行sleep
    }
    close(fds[0]);
    cout << "父进程关闭读端" << endl;

    int status = 0;
    n = waitpid(id, &status, 0);
    assert(n == id);

    cout << "pid->" << n << ":" << (status & 0x7f) << endl;

    // // 0,1,2->3,4
    // //[0]:读取
    // //[1]:写入
    // cout << "fds[0]:" << fds[0] << endl;
    // cout << "fds[1]:" << fds[1] << endl;

    return 0;
}