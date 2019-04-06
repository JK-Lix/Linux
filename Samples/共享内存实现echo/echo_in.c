/*************************************************************************
	> File Name: echo.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年04月06日 星期六 19时15分33秒
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <stdlib.h>
#include <sys/shm.h>
 

#define TEXT_SIZE 2048
struct shared_use_st
{
    int written; //作为一个标志，非0表示可读，0表示可写
    char text[TEXT_SIZE];
};
 
int main()
{
    int running = 1;
    void* shm = NULL;
    struct shared_use_st *shared = NULL;
    char buffer[BUFSIZ + 1];//用于保存输入的文本
    int shmid;
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "shmget fail\n");
        exit(EXIT_FAILURE);
    }
    //将共享内存连接到当前进程的地址空间
    shm = shmat(shmid,  (void*)0, 0);
    if (shm == (void*) -1)
    {
        fprintf(stderr, "shmat fail\n");
    }
    printf("Memory attached at %x\n", (int*)shm);
    //设置共享内存
    shared = (struct shared_use_st *)shm;
    while (running)  //向内存共享中写入数据
    {
        //数据还没有被读取，则等待数据被读取，不能向共享内存中写入文本
        while (shared->written == 1)
        {
            sleep(1);
        }
        //向共享内存中写入数据
        printf("Enter your text:\n");
        fgets(buffer , BUFSIZ, stdin);
        strncpy(shared -> text, buffer, TEXT_SIZE);
        //写完数据，设置written使共享内存可读
        shared -> written = 1;
        //输入end，退出循环
        if (strncmp(buffer, "end", 3) == 0)
        {
            running = 0;
        }
    }
    //把内存共享从当前进程中分离
    if (shmdt(shm) == -1)
    {
        fprintf(stderr, "shmdt fail\n");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    puts("exit_success\n");
    exit(EXIT_SUCCESS);
}
