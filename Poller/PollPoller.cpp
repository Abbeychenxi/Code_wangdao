//
//  PollPoller.cpp
//  Poller
//
//  Created by 陈希 on 14-8-6.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "PollPoller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

#define ERR_EXIT(m)\
    do {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

PollPoller::PollPoller(int listenfd)
:listenfd_(listenfd)
{
    int i;
    for (i=0; i != 2048; ++i) {
        event_[i].fd = -1;
    }
    event_[0].fd = listenfd;
    event_[0].events = POLLIN;
    maxi_ = 0;
    nready_ = 0;
}

void PollPoller::poll()
{
    int ret;
    do {
        ret = ::poll(event_, maxi_ + 1, 10000);
    }while (ret == -1 && errno == EINTR);
    if (ret == -1) {
        ERR_EXIT("poll");
    }
    nready_ = ret;
    cout << "poll" << ret << endl;
}

void PollPoller::handleAccept()
{
    if (nready_ == 0) {
        return;
    }
    if (event_[0].revents & POLLIN) {
        int peerfd;
        if ((peerfd = ::accept(listenfd_, NULL, NULL)) == -1) {
            ERR_EXIT("accept");
        }
        cout << "Accept a peerfd" << peerfd << endl;
        handleConnectionEvent(peerfd);
    }
}

void PollPoller::handleData()
{
    int i;
    char buf[100];
    for (i=1; i <= maxi_; ++i) {
        int peerfd = event_[i].fd;
        if (peerfd == -1) {
            continue;
        }
        
        cout << "Handle" << peerfd << endl;
        
        if (event_[i].revents & POLLIN) {
            int ret = recv(peerfd, buf, sizeof buf, MSG_PEEK);
            cout << "Recv" << ret << endl;
            if (ret == -1) {
                ERR_EXIT("recv");
            }
            if (ret == 0) {
                handleCloseEvent(i);
            }else {
                handleMessageEvent(peerfd);
            }
        }
    }
}

void PollPoller::handleConnectionEvent(int peerfd)
{
    int i;
    for (i=0; i < 2048; ++i) {
        if (event_[i].fd == -1) {
            event_[i].fd = peerfd;
            event_[i].events = POLLIN;
            if (i > maxi_) {
                maxi_ = i;
            }
            break;
        }
    }
    if (i == 2048) {
        fprintf(stderr, "too many clients");
        exit(EXIT_FAILURE);
    }
    TcpConnectionPtr conn(new TcpConnection(peerfd));
    conn->setConnectionCallback(onConectionCallback_);
    conn->setMessageCallback(onMessageCallback_);
    conn->setCloseCallback(onCloseCallback_);
    
    lists_.insert(make_pair(peerfd, conn));
    conn->handleConnection();
}


void PollPoller::handleMessageEvent(int peerfd)
{
    TcpConnectionIterator it = lists_.find(peerfd);
    assert(it != lists_.end());
    cout << "Handle Message" << peerfd <<endl;
    it->second->handleMessage();
}

void PollPoller::handleCloseEvent(int i)
{
    assert(i >= 0 && i < 2048);
    int peerfd = event_[i].fd;
    TcpConnectionIterator it = lists_.find(peerfd);
    assert(it != lists_.end());
    cout << "handle close" << peerfd << endl;
    it -> second -> handleClose();
    lists_.erase(it);
    
    event_[i].fd = -1;
}

