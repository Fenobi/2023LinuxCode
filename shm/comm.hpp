#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATHNAME "."
#define PROJ_ID 0x66
// 共享内内存的大小，一般建议是4KB的整数倍
// 系统分配的共享内存是以4KB为单位的 --- 内存划分内存块的基本单位Page
#define MAX_SIZE 4096 // --- 内核给你的会向上取整

key_t getKey()
{
    key_t k = ftok(PATHNAME, PROJ_ID); // 可以获取同样一个Key
    if (k < 0)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(1);
    }
}

int getShmHelper(key_t k, int flags)
{
    int shmid = shmget(k, MAX_SIZE, flags);
    if (shmid < 0)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
        exit(2);
    }
    return shmid;
}

int getShm(key_t k)
{
    return getShmHelper(k, IPC_CREAT /*0*/);
}

int createShm(key_t k)
{
    return getShmHelper(k, IPC_CREAT | IPC_EXCL | 0600);
}

void *attachShm(int shmid)
{
    void *mem = shmat(shmid, nullptr, 0);
    if ((long long)mem == -1LL)
    {
        std::cerr << "shmat:" << errno << ":" << strerror(errno) << std::endl;
        exit(3);
    }
    return mem;
}

void detachShm(void *start)
{
    if (shmdt(start) == -1)
    {
        std::cerr << "shmdt:" << errno << ":" << strerror(errno) << std::endl;
    }
}

void delShm(int shmid)
{
    if (shmctl(shmid, IPC_RMID, nullptr) == -1)
    {
        std::cerr << errno << ":" << strerror(errno) << std::endl;
    }
}

#endif
