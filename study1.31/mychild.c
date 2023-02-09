#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    pid_t id=fork();
    assert(id!=-1);

    if(id==0)
    {
        //child
        int cnt=5;
        while(cnt)
        {
            printf("child running, pid: %d, ppid: %d, cnt:%d\n", getpid(), getppid(), cnt--);
            sleep(1);
        }
        
        exit(123);
    }

    //parent
    int status=0;
    //1、让OS释放子进程的僵尸状态
    //2、获取子进程的推出结果
    //在等待期间，子进程没有退出的时候，父进程只能阻塞等待
    int ret=waitpid(id,&status,0);
    if(ret>0)
    {
        //是否正常退出
        if(WIFEXITED(status))
        {
            //判断子进程运行结果是否ok
            printf("exit code: %d\n",WEXITSTATUS(status));
        }
        printf("wait success, exit code: %d, sig: %d\n",(status>>8)&0xFF, status & 0x7F);
    }

    return 0;
}
