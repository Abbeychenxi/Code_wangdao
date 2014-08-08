//
//  Rio.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__Rio__
#define __Poll__Rio__

#include <iostream>
#include "NonCopyable.h"
#include <stdio.h>
#define MAXLINE 1024
#define RIO_BUFFER 8192

class Rio : NonCopyable
{
public:
    explicit Rio(int fd);
    
    ssize_t readn(char *usrbuf, size_t n);
    ssize_t readline(char *usrbuf, size_t n);
    ssize_t writen(const char *usrbuf, size_t n);
    
private:
    ssize_t read(char *usrbuf, size_t n);
    
    int fd_;
    int left_;
    char *bufptr_;
    char buffer_[RIO_BUFFER];
};


#endif /* defined(__Poll__Rio__) */
