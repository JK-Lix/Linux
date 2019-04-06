/*************************************************************************
	> File Name: 3.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年03月17日 星期日 18时34分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../common/common.h"
int main() {
    int fd;
    int cnt = 1;
    fd = socket_create(8731, 88);
    while (1) {
        int sfd = accept(fd, NULL, NULL);
        if (sfd > 0) {
            printf("%d", cnt++);
        }
    }
    return 0;
}
