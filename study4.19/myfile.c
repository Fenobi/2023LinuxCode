#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int main()
// {
//     //close(0); // 关闭标准输入
//    // close(1); // 关闭标准输出
//    // close(2); // 关闭标准错误

//     umask(0);
//     int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     if(fd<0)
//     {
//         perror("open fail");
//         return 1;
//     }
//     int t = 0;
//     //scanf("%d", &t);
//     fscanf(stdin, "%d", &fd);
//     printf("open fd: %d\n", fd);
//     //fprintf(stdout, "open fd: %d\n", fd);

//     fflush(stdout);
//     close(fd);
//     return 0;
// }

int main()
{
    umask(0);
    //int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
   // int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    int fd = open("log.txt", O_RDONLY, 0666);
    if(fd<0)
    {
        perror("open fail");
        return 1;
    }
    
    //重定向
    dup2(fd, 0);
   
    char line[64];//输入重定向

    while(1)
    {
        printf("> ");
        if(fgets(line,sizeof(line),stdin) == NULL)
            break;
        printf("%s", line);
    }
    // dup2(fd, 1);
    // printf("open file:%d\n", fd);
    // fprintf(stdout,"open file:%d\n", fd);

    // const char *msg = "hello world";
    // write(1, msg, strlen(msg));

    fflush(stdout);
    close(fd);
    return 0;
}
