/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-06 16:36:52
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-07 10:34:11
 * @FilePath: /fu/2023code/study2.06/myexec.c
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("process is running...\n");
    pid_t id = fork();
    assert(id != -1);

    if (id == 0)
    {
        sleep(1);
        execvp(argv[1], &argv[1]);
        /*char *const argv_[] = {
            "ls",
            "-a",
            "-l",
            "--color=auto",
            NULL};
        //execl("./mybin", "mybin", NULL);
        */
        /*char *const envp_[] = {
            (char *)"MYENV=1111222233334444",
            NULL};
        //execle("./mybin", "mybin", NULL, envp_);
        putenv((char *)"MYENV=44332211");
        execle("./mybin", "mybin", NULL, __environ);
        exit(1); // must failed
        */
    }

    int status = 0;
    pid_t ret = waitpid(id, &status, 0);
    if (ret > 0)
    {
        printf("wait success: exit code: %d, sig:%d\n", (status >> 8) & 0xff, status & 0x7f);
    }
    return 0;
}
