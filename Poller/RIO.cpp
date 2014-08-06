//
//  RIO.cpp
//  Poller
//
//  Created by 陈希 on 14-8-6.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "RIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define ERR_EXIT(m)\
    do {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

Rio::Rio(int fd)
:fd_(fd),
left_(0),
bufptr_(buffer_)
{
    
}

ssize_t Rio::read(char *usrbuf, size_t n)
{
    ssize_t nread;
    while (left_ <= 0) {
        nread = ::read(fd_, buffer_, sizeof buffer_);
        if (nread == -1) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }else if (nread == 0)
            return 0;
        
        left_ = nread;
        bufptr_ = buffer_;
    }
    int cnt = n;
    if (left_ < n) {
        cnt = left_;
    }
    ::memcpy(usrbuf, bufptr_, cnt);
    left_ -= cnt;
    bufptr_ += cnt;
    
    return cnt;
}

ssize_t Rio::readn(char *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;
    
    while (nleft > 0) {
        if ((nread = read(bufp, nleft)) == -1) {
            return -1;
        }else if(nread == 0)
            break;
        
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t Rio::readline(char *usrbuf, size_t maxlen)
{
    char *bufp = usrbuf;
    char c;
    int nread;
    int i;
    for (i=0; i < maxlen - 1; i++) {
        if ((nread = read(&c, 1)) == -1) {
            return -1;
        }else if(nread == 0)
        {
            if (i == 0) {
                return 0;
            }
            break;
        }
        *bufp++ = c;
        if (c == '\n') {
            break;
        }
    }
    *bufp = '\0';
    return i;
}

ssize_t Rio::writen(const char *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwrite;
    
    const char *bufp = usrbuf;
    
    while (nleft > 0) {
        if ((nwrite = write(fd_, bufp, nleft)) == -1) {
            if (errno == EINTR) {
                nwrite = 0;
            }else{
                return -1;
            }
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;
}