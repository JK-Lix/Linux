/*************************************************************************
	> File Name: epoll.c
	> Author: Lix
	> Mail: 776579471@qq.com
	> Created Time: 2019年04月04日 星期四 19时19分19秒
 ************************************************************************/

#include <stdio.h>
#include <sys/epoll.h>
#include "../../Project/MyChatRoom/common/common.h"
#define MAX_EVENTS 500

int main() {
    int server_listen;
    if ((server_listen = socket_create(7731)) < 0) {
        perror;
    }

    int epollfd;
    epollfd = epoll_create(500);

    struct epoll_event ev, event[MAX_EVENTS];
    ev.events = EPOLLIN;
    ev.data.fd = server_listen;

    epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &ev);
    
    while(1) {
        int nfds = epoll_wait(epollfd, event, MAX_EVENTS, -1);
        for (int i = 0; i < nfds; ++i) {
            if (event[i].data.fd == server_listen && event[i].events & EPOLLIN) {
                int sockfd = accept(server_listen, NULL, NULL);
                if (sockfd == -1) perror("accept");
                ev.data.fd = sockfd;
                ev.events = EPOLLIN;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev);
            } else if (event[i].events & EPOLLIN) {
                char buff[1024] = {0};
                int recvn = recv(event[i].data.fd, buff, sizeof(buff), 0);
                if (recvn == 0) {
                    ev.data.fd = event[i].data.fd;
                    close(ev.data.fd);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, event[i].data.fd, &ev);
                } else {
                    printf("%s\n", buff);
                    fflush(stdout);
                    ev.events = EPOLLOUT;
                    ev.data.fd = event[i].data.fd;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, event[i].data.fd, &ev);
                }
            } else if (event[i].events & EPOLLOUT) {
                send(event[i].data.fd, "You are Here!", 14, 0);
                ev.events = EPOLLIN;
                ev.data.fd = event[i].data.fd;
                epoll_ctl(epollfd, EPOLL_CTL_DEL, event[i].data.fd, &ev);
            }
        }
    }
    return 0;
}
