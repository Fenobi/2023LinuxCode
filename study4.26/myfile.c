#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    //c接口
    printf("hello printf\n");
    fprintf(stdout, "hello fprintf\n");
    fputs("hello fput\n", stdout);

    //system接口
    const char *msg = "hello write\n";
    write(1, msg, strlen(msg));

    fork();//加上这个函数后，进行重定向时，system接口打印一次，c接口打印两次
    
    fflush(stdout);
    return 0;
}
