#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>

#define Make_Rand() srand((unsigned long)time(nullptr) ^ getpid() ^ 0x121243 ^ rand() % 1234)

#define PROCSS_NUM 5

//////////////////////////////////任务区//////////////////////////////////////////////
typedef void (*func_t)();

void downLoadTask()
{
    std::cout << getpid() << ":下载任务\n"
              << std::endl;
    sleep(1);
}

void ioTask()
{
    std::cout << getpid() << ":IO任务\n"
              << std::endl;
    sleep(1);
}

void flushTash()
{
    std::cout << getpid() << ":刷新任务\n"
              << std::endl;
    sleep(1);
}

void loadTaskFunc(std::vector<func_t> *out)
{
    assert(out);
    out->push_back(downLoadTask);
    out->push_back(ioTask);
    out->push_back(flushTash);
}

//////////////////////////////////子进程实现区////////////////////////////////////////
struct subEp
{
public:
    subEp(pid_t subId, int writeFd)
        : _subId(subId), _writeFd(writeFd)
    {
        char nameBuffer[1024];
        snprintf(nameBuffer, sizeof nameBuffer, "process-%d[pid(%d)-df(%d)]", num++, _subId, _writeFd);
        _name = nameBuffer;
    }

public:
    static int num;
    std::string _name;
    pid_t _subId;
    int _writeFd;
};

int subEp::num = 0;

void sendTask(const subEp &process, int taskNum)
{
    std::cout << "send task num:" << taskNum << " send to->" << process._name << std::endl;
    int n = write(process._writeFd, &taskNum, sizeof taskNum);
    assert(n == sizeof(int));
    (void)n;
}

int recvTask(int readFd)
{
    int code = 0;
    ssize_t s = read(readFd, &code, sizeof code);
    if (s == 4)
        return code;
    else if (s <= 0)
        return -1;
    else
        return 0;
}

void createSubProcess(std::vector<subEp> *subs, std::vector<func_t> &funcMap)
{
    std::vector<int> deleteFd;
    for (int i = 0; i < PROCSS_NUM; ++i)
    {
        int fds[2];
        int n = pipe(fds);
        assert(n == 0);
        (void)n;
        // bug?
        // 在父进程创建第一个子进程后，后面的子进程也会继承父进程创建的写子进程的管道
        pid_t id = fork();
        if (id == 0)
        {
            // bug解决方法（关闭上一个的文件描述符）
            for (int i = 0; i < deleteFd.size(); ++i)
                close(deleteFd[i]);
            // 子进程，进行处理任务
            close(fds[1]);
            while (true)
            {
                // 1、获取命令码，如果没有发送，我们子进程应该阻塞
                int commandCode = recvTask(fds[0]);
                // 2、完成任务
                if (commandCode >= 0 && commandCode < funcMap.size())
                    funcMap[commandCode]();
                else if (commandCode == -1)
                    break;
            }
            exit(0);
        }
        close(fds[0]);
        subEp sub(id, fds[1]);
        subs->push_back(sub);
        deleteFd.push_back(fds[1]);
    }
}

void loadBanceContrl(const std::vector<subEp> &subs, const std::vector<func_t> &funcMap, int count)
{
    int processnum = subs.size();
    int tasknum = funcMap.size();
    bool forever = (count == 0 ? true : false);
    while (true)
    {
        // 1、选择一个子进程 --> std::vector<subEp> -> index 随机数
        int subIdx = rand() % processnum;
        // 2、选择一个任务 --> std::vector<func_t> -> index 随机数
        int taskIdx = rand() % tasknum;
        // 3、将任务发送给选择的进程
        sendTask(subs[subIdx], taskIdx);

        sleep(1);
        if (!forever)
        {
            --count;
            if (count == 0)
                break;
        }
    }
    // write quit -> read 0
    for (int i = 0; i < processnum; ++i)
    {
        close(subs[i]._writeFd);
    }
}

void waitProcess(std::vector<subEp> processes)
{
    int processnum = processes.size();
    for (int i = 0; i < processnum; ++i)
    {
        waitpid(processes[i]._subId, nullptr, 0);
        std::cout << "wait sub process success ..." << processes[i]._subId << std::endl;
    }
}

int main()
{
    Make_Rand();
    // 1、建立子进程并建立子进程通信的信道
    // [子进程id,wfd]
    // 1.1 加载方法表
    std::vector<func_t> funcMap;
    loadTaskFunc(&funcMap);
    // 1.2 创建子进程，并且维护号父子通信信道
    std::vector<subEp> subs;
    createSubProcess(&subs, funcMap);

    // 2、走到这里就是父进程，控制子进程，负载均匀的向子进程发送命令码
    int taskCnt = 3;
    loadBanceContrl(subs, funcMap, taskCnt);

    // 3、回收子进程信息
    waitProcess(subs);

    return 0;
}
