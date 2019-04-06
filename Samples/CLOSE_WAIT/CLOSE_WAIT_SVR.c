/*************************************************************************
	> File Name: 2.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年03月17日 星期日 18时24分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../common/common.h"

int main(int argc, char *argv[]) {
    int fd;
    for (int i = 0; i < 88; i++) {
        fd = socket_connect(8731, argv[1]);
        if (fd > 0) {
            printf("success");
            close(fd);
        } 
    }
    return 0;
}
