/*************************************************************************
	> File Name: sum.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年03月02日 星期六 09时17分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>
#include<pthread.h>

typedef struct Para{
    int get;
    int part;
}Para;

int allsum = 0;
pthread_mutex_t now_t;

void* sum(void* argv) {
//    pthread_mutex_lock(&now_t);
    Para *para;
    para = (Para*)argv;
    para->get += para->part;
    int part = para->part;
    int get  = para->get;
    printf("%d...%d\n", get, get + part);
    for (int i = para->get; i < para->get + para->part; i++) {
        allsum += i;
    }
//    pthread_mutex_unlock(&now_t);
}

int spow(int a, int b) {
    int num = 1;
    for (int i = 0; i <b; i++) {
        num *= a;
    }
    return num;
}

int get_num(char *size){
    int n = sizeof(size) - 1;
    int num = 0;
    for (int i = 0; i < sizeof(size); i++) {
        num += (size[i] - '0') * spow(10, n);
        n--;
    }
    return num;
}

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    int n = atoi(argv[2]);
    pthread_t pid[n];
    printf("aaa%d...%d\n",num, n);
    int part = num / n;
    Para para;
    para.part = part;
    para.get = 0 - part;
    for(int i = 0; i < n; i++) {   
        pthread_create(&pid[i], NULL, sum, (void*)&para);
    }
    for(int i = 0; i < n; i++) {
        pthread_join(pid[i], NULL);
    }
    allsum += num;
    printf("%d\n", allsum);
    return 0;
}
