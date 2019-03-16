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
    int a[4],i;
    char b[20];
    
    
    sprintf(b,"%d.", a[0] = ((inaddr & 0x000000ff)));
    sprintf(b,"%s%d.", b, a[1] = ((inaddr & 0x0000ff00) >> 8));
    sprintf(b,"%s%d.", b, a[2] = ((inaddr & 0x00ff0000) >> 16));
    sprintf(b,"%s%d", b, a[3] = ((inaddr & 0xff000000) >> 24));
    sprintf(str, "%s", b);

    return str;
    
}

int main() {
    unsigned long inaddr = 0x4102a8c0;
    printf("%s\n", my_inet_ntoa(inaddr));
    return 0;
}
