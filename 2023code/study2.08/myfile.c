/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-08 11:48:59
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-08 17:31:17
 * @FilePath: /fu/2023code/study2.08/myfile.c
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define FILE_NAME "log.txt"

int main()
{
    umask(0);
    // O_TRUNC:写入前清空内容
    // int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    // O_APPEND:追加
    // int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_APPEND, 0666);
    // O_RDONLY:读取
    int fd = open(FILE_NAME, O_RDONLY);

    //  assert(fd != -1);
    // (void)fd;
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    /* int cnt = 5;
    char outBuffer[64];
    while(cnt)
    {
        sprintf(outBuffer, "%s: %d\n", "you are kenobi", cnt--);
        write(fd, outBuffer, strlen(outBuffer));
    } */

    char buffer[1024];
    ssize_t num = read(fd, buffer, sizeof(buffer) - 1);
    if (num > 0)
    {
        buffer[num] = '\0';
    }
    printf("%s", buffer);
    // printf("fd: %d\n", fd);
    close(fd);
    return 0;
}