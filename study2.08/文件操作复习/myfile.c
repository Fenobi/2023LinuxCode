/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-08 11:48:59
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-08 16:51:08
 * @FilePath: /fu/2023code/study2.08/文件操作复习/myfile.c
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "log.txt"

int main()
{
    //细节问题
    //以w方式单纯的打开文件，会清空文件中的内容
    //0666 & ~umask
    //FILE *fp = fopen(FILE_NAME, "w"); // r,w,r+(读写,不存在出错),w+(读写，不存在创建),r+b,w+b,a(append,追加),a+
    FILE *fp = fopen(FILE_NAME, "r"); // r,w,r+(读写,不存在出错),w+(读写，不存在创建),r+b,w+b,a(append,追加),a+
    //FILE *fp = fopen(FILE_NAME, "a"); // r,w,r+(读写,不存在出错),w+(读写，不存在创建),r+b,w+b,a(append,追加),a+
    if (NULL == fp)
    {
        perror("fopen");
        return 1;
    }
    /*int cnt = 5;
    while(cnt)
    {
        fprintf(fp, "%s:%d\n", "kenobi", cnt--);
    }  */
    char buffer[64];
    while (fgets(buffer, sizeof(buffer) - 1, fp) != NULL)
    {
        buffer[strlen(buffer) - 1] = 0;
        puts(buffer);
    }
    fclose(fp);
    return 0;
}