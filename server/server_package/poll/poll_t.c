#include "poll_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

void poll_add_fd(poll_t *_poll, int fd);
void poll_del_fd(poll_t *_poll, int i);

void poll_init(poll_t *_poll,
                int listenfd,
                void(*handler)(int, char*))
{
    int i;
    for(i = 0; i < 2048; i++)
    {
        _poll->clients_[i].fd = -1;
    }
    _poll->listenfd_ = listenfd;
    _poll->clients_[0].fd = listenfd;
    _poll->clients_[0].events = POLLIN;

    _poll->maxi_ = 0;
    _poll->handle_callback_ = handler;
    _poll->nready_ = 0;
}

void poll_do_wait(poll_t *_poll)
{
    int nready;
    do{
        nready = poll(_poll->clients_, _poll->maxi_ + 1, -1);
    }while(nready == -1 && errno == EINTR);
    if (nready == -1)
    {
        ERR_EXIT("poll");
    }
    _poll->nready_ = nready;
}

void poll_handle_accept(poll_t *_poll)
{
    if (_poll->clients_[0].revents & POLLIN)
    {
        int peerfd = accept(_poll->listenfd_, NULL, NULL);
        if (peerfd == -1)
        {
            ERR_EXIT("accept");
        }
        poll_add_fd(_poll, peerfd);
    }
}

void poll_handle_data(poll_t *_poll)
{
    int i;
    char recvbuf[1024];
    for(i = 1; i<= _poll->maxi_; ++i)
    {
        int peerfd = _poll->clients_[i].fd;
        if(peerfd == -1)
            continue;
        if (_poll->clients_[i].revents & POLLIN)
        {
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("client close\n");
                poll_del_fd(_poll, i);
                continue;
            }
            _poll->handle_callback_(peerfd, recvbuf);
        }
    }
}


void poll_add_fd(poll_t *_poll, int fd)
{
    int i;
    for(i = 1; i<2048; ++i)
    {
        if (_poll->clients_[i].fd == -1)
        {
            _poll->clients_[i].fd = fd;
            _poll->clients_[i].events = POLLIN;
            if(i > _poll->maxi_)
                _poll->maxi_ = i;
            break;
        }
    }
    if(i == 2048)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }
}

void poll_del_fd(poll_t *_poll, int i)
{
    assert(i >= 1 && i<2048);
    close(_poll->clients_[i].fd);
    _poll->clients_[i].fd = -1;}