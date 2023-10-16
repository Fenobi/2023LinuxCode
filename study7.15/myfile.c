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

    // 代码结束之前，进行创建子进程
    // 1.如果我们没有进行 > ,看到了4条消息：
    // stdout 默认使用的是行刷新，在进程fork之前，三条C函数已经将数据进行打印输出到显示器上（外设），你的FILE内部，进程内部不存在对应的数据了
    // 2.如果我们进行了 > ,写入文件不再是显示器了，而是普通文件：
    // 所以采用的刷新策略是全缓冲，之前的3条C显示函数，虽然带了\n，但是不足以将stdout缓冲区写满！数据并没有被刷新！
    // 而执行fork的时候，stdout属于父进程，创建子进程时，紧接着就是进程退出！谁先退出，一定要进行缓冲区刷新（就是修改）
    // 发生写时拷贝！！数据最终会显示两份
    // 3.write为什么没有呢？上面的过程都和write无关，write没有FILE，而用的时fd，就没有C提供的缓冲区
    fork();//加上这个函数后，进行重定向时，system接口打印一次，c接口打印两次
    
    //fflush(stdout);
    return 0;
}
