#include "comm.hpp"

int main()
{
    key_t k = getKey();
    printf("0x%x\n", k);

    int shmid = createShm(k);
    printf("%d\n", shmid);
    sleep(5);

    char* start = (char*)attachShm(shmid);
    printf("attach success,address start:%p\n", start);
    
    //使用
    while(true)
    {
        printf("client say : %s\n", start);

        struct shmid_ds ds;
        shmctl(shmid, IPC_STAT, &ds);
        printf("获取属性: size: %d,pid:%d,myself: %d", ds.shm_segsz, ds.shm_cpid, getpid());

        sleep(1);
        
    }

    //去关联
    detachShm(start);

    sleep(10);
    // 释放共享内存
    delShm(shmid);

    return 0;
}