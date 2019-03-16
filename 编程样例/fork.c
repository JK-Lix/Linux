/*************************************************************************
	> File Name: fork.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年03月02日 星期六 19时33分54秒
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    printf("%s\n", "我是鸣人！");
    int pid = fork();
    if (pid != 0) {
        int status;
        int result = wait(&status);
        if (result == -1 || status != 0) {
            printf("%s\n", "可恶，又失败了，再来一次！");
            return -1;
        } else {
			printf("%s\n", "我负责性质变化！");
        }
    } else {
        int second_pid = fork();
        if (second_pid != 0) {
            int new_status;
            int new_result = wait(&new_status);
            if (new_result == -1 || new_status != 0) {
				exit(-1);
            } else {
				printf("%s\n", "我负责形态变化！");
        		exit(0);
            }
        } else {
            printf("%s\n", "我负责产生查克拉！");
            exit(0);
        }
    }
    return 0;
}
