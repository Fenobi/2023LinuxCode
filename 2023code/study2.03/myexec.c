/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-03 14:32:51
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-06 17:04:32
 * @FilePath: /fu/2023code/study2.03/myexec.c
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    printf("process is running...\n");
    pid_t id = fork();
    assert(id != -1);

    if (id == 0)
    {
        sleep(1);
        // execl("/usr/bin/ls", "ls", "-a", "-l", "--color=auto", NULL);
        // execlp("ls", "-a", "-l", "--color=auto", NULL);
        char *const argv_[] = {
            "ls",
            "-a",
            "-l",
            "--color=auto",
            NULL};
        // execv("/usr/bin/ls", argv_);
        execvp("ls", argv_);
        

        exit(1); // must failed
    }

    int status = 0;
    pid_t ret = waitpid(id, &status, 0);
    if (ret > 0)
    {
        printf("wait success: exit code: %d, sig:%d\n", (status >> 8) & 0xff, status & 0x7f);
    }

    // //.c -> exe -> load ->process -> 运行 ->执行我们现在所写的代码
    // printf("process is running...\n");

    // // load -> exe
    // int n = execl("/usr/bin/ls" /*要执行哪一个程序*/, "ls", "-a", "-l", "--color=auto", NULL /*你想怎么执行*/); // all exec* end of NULL;
    // // execl("/bin/top" /*要执行哪一个程序*/ ,"top",NULL /*你想怎么执行*/ );//all exec* end of NULL;
    // if (n == -1)
    // {
    //     printf("error\n");
    // }
    // printf("process running done...\n");

    return 0;
}
