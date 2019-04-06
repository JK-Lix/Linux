/*************************************************************************
	> File Name: echo2.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年04月06日 星期六 19时23分41秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>


#define TEXT_SIZE 2048
struct shared_use_st{
   int written; //作为一个标志，非0表示可读，0表示可写
    char text[TEXT_SIZE];
};

int main() {
    int running = 1;//程序是否运行标志
    void *shm = NULL;//分配的共享内存的原始首地址
    struct shared_use_st *shared = NULL; //指向内存
    int shmid;//共享内存标识符
    //创建共享内存
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    //将共享内存连接到当前进程的地址空间
    shm = shmat(shmid, 0, 0);
    if (shm == (void *) - 1)
    {
        fprintf(stderr, "shmat failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n", (int*)shm);
    //设置内存共享
    shared = (struct shared_use_st *)shm;
    shared->written = 0;
    while (running)//读取共享内存中的数据
    {
        //没有进程共享内存数据可读取
        if (shared->written != 0)
        {
            printf("echo: %s", shared->text);
            sleep(rand() % 3);
            //读完数据，设置written使共享内存可读
            shared->written = 0;
            //输入end,退出循环
            if (strncmp(shared->text, "end", 3) == 0)
            {
                running = 0;
            }
        } else
        {
            sleep(1);
        }
    }
    //把共享内存从当前进程分离
    if (shmdt(shm) == -1)
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    //删除共享内存
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    puts("exit success\n");
    exit(EXIT_SUCCESS);
}
