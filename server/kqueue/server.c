#include "network.h"
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

struct event
{
    int fd;
    void (*handle)(struct event*);
};

int get_listen_fd();
void do_kqueue(int listenfd);
static void listen_readable(struct event *e)
{
    int connfd;

    connfd = accept(e->fd, NULL, NULL);
    printf("connfd = %d\n", connfd);
    char recvbuf[1024] = {0};
    while(1)
    {
        int ret = readline(connfd, recvbuf, 1024);
        if (ret == -1)
        {
            ERR_EXIT("readline");
        }else if(ret == 0)
        {
            printf("client close\n");
            close(connfd);
            break;
        }
        printf("recv data: %s", recvbuf);
        writen(connfd, recvbuf, strlen(recvbuf));
    }
}

int main(int argc, char const *argv[])
{
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        ERR_EXIT("signal");
    }
    int listenfd = get_listen_fd();

    do_kqueue(listenfd);   


    close(listenfd);

    return 0;
}

int get_listen_fd()
{
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        ERR_EXIT("setsockopt");
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8989);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof servaddr) < 0)
    {
        ERR_EXIT("bind");
    }

    if (listen(listenfd, SOMAXCONN) < 0)
    {
        ERR_EXIT("listen");
    }
    return listenfd;
}
void do_kqueue(int listenfd)
{
    int kq;
    int nfds;
    struct kevent ev,rev[2];

    if ((kq = kqueue()) == -1)
    {
        close(kq);
        ERR_EXIT("kqueue");
    }

    struct event e;
    e.fd = listenfd;
    e.handle = listen_readable;

    EV_SET(&ev, listenfd, EVFILT_READ, EV_ADD, 0, 0, &e);

    while(1)
    {
        nfds = kevent(kq, &ev, 1, rev, 2, NULL);
        if (nfds <= 0)
        {
            close(kq);
            ERR_EXIT("kevent");
        }
        for (int i = 0; i < nfds; ++i)
        {
            struct event *re = rev[i].udata;
            if (re)
            {
                re->handle(re);
            }
        }
    }
}