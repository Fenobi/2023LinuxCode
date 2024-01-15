#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

volatile int quit = 0;

void handler(int signo)
{
    printf("%d 号信号，正在被捕捉！\n", signo);
    printf("quit: %d", quit);
    quit = 1;
    printf("->%d\n", quit);
}

int main()
{
    signal(2, handler);
    while(!quit)
        ;
    printf("注意，我是正常退出的！\n");
    return 0;
}
