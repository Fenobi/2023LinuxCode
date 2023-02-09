/*
 * @Author: Fenobi 1366773912@qq.com
 * @Date: 2023-02-06 16:36:52
 * @LastEditors: Fenobi 1366773912@qq.com
 * @LastEditTime: 2023-02-06 16:58:23
 * @FilePath: /fu/2023code/study2.06/mybin.c
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    //系统就有的
    printf("PATH,%s\n", getenv("PATH"));
    printf("PWD,%s\n", getenv("PWD"));
    //自定义的
    printf("MYENV,%s\n", getenv("MYENV"));
    printf("我是一个c语言程序\n");

    return 0;
}