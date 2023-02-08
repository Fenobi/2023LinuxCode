/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-08 11:24:20
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-08 11:24:21
 * @FilePath: /fu/2023code/study2.07/myshell.c
 */
/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-07 10:35:25
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-08 10:55:05
 * @FilePath: /fu/2023code/study2.07/myshell.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>

#define NUM 1024
#define OPT_NUM 64

char lineCommand[NUM];
char *myargv[OPT_NUM];

int main()
{
    while (1)
    {
        // 输出提示符
        printf("fu@vscode %s# ", getenv("PWD"));
        fflush(stdout);

        // 获取用户输入,输入时会输入\n
        char *s = fgets(lineCommand, sizeof(lineCommand) - 1, stdin);
        assert(s != NULL);
        (void)s;
        // 清除最后一个\n
        lineCommand[strlen(lineCommand) - 1] = 0;
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
        assert(i != -1);

        if (id == 0)
        {
            execvp(myargv[0], myargv);
            exit(1);
        }

        waitpid(id, NULL, 0);
    }

    return 0;
}