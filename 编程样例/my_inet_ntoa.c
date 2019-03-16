/*************************************************************************
	> File Name: my_inet_aton.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年03月16日 星期六 10时07分50秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include <arpa/inet.h>

char str[30];

char* my_inet_ntoa(unsigned long inaddr) {
    int a[4];
    
    a[0] = ((inaddr & 0x000000ff));
    a[1] = ((inaddr & 0x0000ff00) >> 8);
    a[2] = ((inaddr & 0x00ff0000) >> 16);
    a[3] = ((inaddr & 0xff000000) >> 24);
    
    sprintf(str, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
    return str;
    
}

int main() {
    unsigned long inaddr = 0x4102a8c0;
    printf("%s\n", my_inet_ntoa(inaddr));
    return 0;
}
