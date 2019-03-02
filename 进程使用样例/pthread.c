/*************************************************************************
	> File Name: pthread.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年02月26日 星期二 18时22分13秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>
#include<pthread.h>

struct Mypara{
    char name[20];
    int age;
};     //定义参数结构体

void *print(void *argv) { //定义回传函数
    char name[20] = {0};
    struct Mypara *para;

    para = (struct Mypara *)argv;
                         //将创建线程函数传来的参数指针转化为参数结构体
    
    printf("hello %s, Im %d\n", para->name, para->age);
    
    return NULL;
}

int main() {
    pthread_t print_t; //创建线程符
    
    printf("start!\n");
    
    struct Mypara para;
    char name_in[20] = {0};
    int age = 0;
    
    scanf("%s", name_in);
    scanf("%d", &age);
    
    para.age = age;
    strcpy(para.name, name_in);

    pthread_create(&print_t, NULL, print, (void *)&para);//创建线程
    pthread_join(print_t, NULL);//等待子线程关闭后再继续执行下面的代码
    
    return 0;
}
