/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-09 11:41:55
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-09 11:49:05
 * @FilePath: /fu/2023code/study2.09/myfile.c
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_NAME "log.txt"

int main()
{
    printf("stdin:%d\n", stdin->_flags);
    int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd<0)
    {
        perror("open");
        reutrn 1;
    }

    close(fd);
    return 0;
}