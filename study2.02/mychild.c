/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-02 20:05:15
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-02 21:52:47
 * @FilePath: /study2.02/mychild.c
 */
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM 10

typedef void (*func_t)();

func_t handlerTask[NUM];

//样例任务
void task1()
{
    printf("handler task1\n");
}

void task2()
{
    printf("handler task2\n");
}

void task3()
{
    printf("handler task3\n");
}

void loadTask()
{
    memset(handlerTask,0,sizeof(handlerTask));
    handlerTask[0]=task1;
    handlerTask[1]=task2;
    handlerTask[2]=task3;
}

void addtaks()
{
    ;
}

int main()
{
    pid_t id=fork();
    assert(id!=-1);

    if(id==0)
    {
        //child
        int cnt=10;
        while(cnt)
        {
            printf("child running, pid: %d, ppid: %d, cnt:%d\n", getpid(), getppid(), cnt--);
            sleep(3);
        }
        
        exit(1);
    }


    loadTask();
    //parent
    int status = 0;
    while(1)
    {
        pid_t ret = waitpid(id,&status,WNOHANG);  //WNOHANG:非阻塞->子进程没有退出，父进程检测的时候，立即返回
        if(ret == 0)
        {
            //waitpid调用成功 && 子进程没退出
            //子进程没有退出，我的waitpid没有等待失败，仅仅是检测到了子进程没退出
            printf("wait done, but child is running... parent running other things\n");
            for(int i=0;handlerTask[i]!=NULL;++i)
            {
                handlerTask[i]();//采用回调的方式，执行我们想让父进程在空闲的时候做的事情
            }
            
        }
        else if(ret > 0)
        {
            //1.waitpid调用成功 && 子进程退出了
            printf("wait success, exit code: %d, sig: %d\n",(status>>8)&0xFF, status & 0x7F);
            break;
        }
        else  //-1
        {
            //waitpid调用失败
            printf("waitpid call failed\n");
            break;
        }
        sleep(1);
    }
    














    
   /* int status=0;
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
*/
    return 0;
}
