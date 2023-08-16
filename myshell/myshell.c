#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define NUM 1024
#define OPT_NUM 64

#define NONE_REDIR   0
#define INTPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3

#define trimSpace(start) do{\
    while(*start == ' ') ++start;\
}while (0)

char lineCommand[NUM];
char *myargv[OPT_NUM];
int lastCode = 0;
int lastSig = 0;

int fileType = NONE_REDIR;
char *redirFile = NULL;

void commandChect(char *commands)
{
    assert(commands);
    char *start = commands;
    char *end = commands + strlen(commands);
    while (start < end)
    {
        if (*start == '>')
        {
            *start = '\0';
            ++start;
            if(*start == '>')
            {
                *start = '\0';
                fileType = APPEND_REDIR;
                ++start;
            }
            else
            {
                fileType = OUTPUT_REDIR;
            }
            trimSpace(start);
            redirFile = start;
            break;
        }
        else if (*start == '<')
        {
            *start = '\0';
            ++start;
            trimSpace(start);
            fileType = INTPUT_REDIR;
            redirFile = start;
            break;
        }
        else
        {
            ++start;
        }
    }
}

int main()
{
    while (1)
    {
<<<<<<< HEAD
        //初始化
=======
        //
>>>>>>> 1ed07d909825058f422e5c544772647b4efb2f64
        fileType = NONE_REDIR;
        redirFile = NULL;
        errno = 0;

        // 输出提示符
        printf("fu@vscode %s# ", getenv("PWD"));
        fflush(stdout);

        // 获取用户输入,输入时会输入\n
        char *s = fgets(lineCommand, sizeof(lineCommand) - 1, stdin);
        assert(s != NULL);
        (void)s;
        // 清除最后一个\n
        lineCommand[strlen(lineCommand) - 1] = 0;

        commandChect(s);
        
        // printf("%s\n", lineCommand);
        // 字符串切割
        myargv[0] = strtok(lineCommand, " ");
        int i = 1;
        // 上颜色
        if (myargv[0] != NULL && strcmp(myargv[0], "ls") == 0)
        {
            myargv[i++] = "--color=auto";
        }

        while (myargv[i++] = strtok(NULL, " "))
            ;

        // 如果是cd命令，不需要创建子进程，让shell自己执行对应的命令，本质就是执行系统接口
        // 像这种不需要让我们的子进程来执行，而是让shell自己执行的命令 -- 内建/内置命令
        if (myargv[0] != NULL && strcmp(myargv[0], "cd") == 0)
        {
            if (myargv[1] != NULL)
            {
                chdir(myargv[1]);
                continue;
            }
        }

        // 测试是否成功
#ifdef DEBUG
        for (int i = 0; myargv[i]; ++i)
        {
            printf("myargv[%d]: %s\n", i, myargv[i]);
        }
#endif

        // 执行命令
        pid_t id = fork();
        assert(id != -1);

        if (id == 0)
        {
            //因为命令是子进程执行的，真正重定向的工作一定时子进程来完成
            //如何重定向，是父进程来给子进程提供信息的
            //这里重定向不会影响父进程
            switch (fileType)
            {
                case NONE_REDIR:
                    //啥也不做
                    break;
                case INTPUT_REDIR:
                    {
                        int fd = open(redirFile, O_RDONLY);
                        if(fd<0)
                        {
                            perror("open fail");
                            exit(errno);
                        }
                        // 重定向的文件已经生成
                        dup2(fd, 0);
                    }
                    break;
                case OUTPUT_REDIR:
                case APPEND_REDIR:
                    {
                        umask(0);
                        int flags = O_WRONLY;
                        if(fileType == APPEND_REDIR)
                            flags |= O_APPEND;
                        else
                            flags |= O_TRUNC;
                        int fd = open(redirFile, flags);
                        if(fd<0)
                        {
                            perror("open fail");
                            exit(errno);
                        }
                        dup2(fd, 1);
                    }
                    break;
                default:
                    printf("bug?\n");
                    break;
            }
            
            execvp(myargv[0], myargv);//执行程序替换的时候，会不会影响曾经进程打开的重定向的文件？不会！
            exit(1);
        }
        
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        assert(ret > 0);
        (void)ret;
        lastCode = ((status >> 8) & 0xff);
        lastSig = (status & 0x7f);
    }

    return 0;
}