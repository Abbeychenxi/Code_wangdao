//
//  Socket.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__Socket__
#define __Poll__Socket__

#include <iostream>
#include "NonCopyable.h"
#include "InetAddress.h"

class Socket : private NonCopyable
{
public:
    explicit Socket(int sockfd);
    ~Socket();
    
    int fd() const
    { return sockfd_; }
    void bindAddress(const InetAddress &addr);
    void listen();
    int accept();
    void shutdownWrite();
    void setReusePort();
    
private:
    const int sockfd_;
};
#endif /* defined(__Poll__Socket__) */
