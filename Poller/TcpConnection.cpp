//
//  TcpConnection.cpp
//  Poller
//
//  Created by 陈希 on 14-8-6.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "TcpConnection.h"
using namespace std;

#define ERR_EXIT(m)\
    do {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

TcpConnection::TcpConnection(int sockfd)
:sockfd_(sockfd),
buffer_(sockfd)
{
    
}

TcpConnection::~TcpConnection()
{
    shutdown();
}

ssize_t TcpConnection::readn(char *usrbuf, size_t n)
{
    int nread = buffer_.readn(usrbuf, n);
    if (nread == -1) {
        ERR_EXIT("readn");
    }
    return nread;
}

ssize_t TcpConnection::readline(char *usrbuf, size_t maxline)
{
    int nread = buffer_.readline(usrbuf, maxline);
    if (nread == -1) {
        ERR_EXIT("readline");
    }
    return nread;
}

ssize_t TcpConnection::writen(const char *usrbuf, size_t n)
{
    int nwrite = buffer_.writen(usrbuf, n);
    if (nwrite == -1) {
        ERR_EXIT("write");
    }
    return nwrite;
}

void TcpConnection::send(const std::string &s)
{
    writen(s.c_str(), s.size());
}

//std::string TcpConnection::receiveString()
//{
//    char buf[1024];
//    readline(buf, 1024);
//    return std::string(buf);
//}

void TcpConnection::shutdown()
{
    sockfd_.shutdownWrite();
}
