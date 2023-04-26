#include "myStdio.h"
#include <stdio.h>

int main()
{
    int cnt = 10;
    FILE_ *fp = fopen_("log.txt", "w");
    if(fp == NULL)
        return 1;
    const char *msg = "hello world!";
    while (1)
    {
        cnt--;
        fwrite_(msg, strlen(msg), fp);
        fflush_(fp);
        sleep(1);

        printf("count:%d\n", cnt);
        if(cnt == 5)
            fflush_(fp);
        if (cnt == 0)
            break;
    }
    fclose_(fp);
    return 0;
}