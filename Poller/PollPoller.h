//
//  PollPoller.h
//  Poller
//
//  Created by 陈希 on 14-8-6.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poller__PollPoller__
#define __Poller__PollPoller__

#include <iostream>
#include "NonCopyable.h"
#include "TcpConnection.h"
#include <map>
#include <poll.h>

class PollPoller: private NonCopyable
{
public:
    typedef TcpConnection::TcpConnectionCallback PollerCallback;
    
    explicit PollPoller(int listenfd);
    void poll();
    void handleAccept();
    void handleData();
    
    void setConnectionCallback(const PollerCallback &cb)
    { onConectionCallback_ = cb; }
    void setMessageCallback(const PollerCallback &cb)
    { onMessageCallback_ = cb; }
    void setCloseCallback(const PollerCallback &cb)
    { onCloseCallback_ = cb; }
    
    void handleConnectionEvent(int peerfd);
    void handleMessageEvent(int peerfd);
    void handleCloseEvent(int index);
    
private:
    struct pollfd event_[2048];
    int listenfd_;
    int maxi_;
    int nready_;
    std::map<int, TcpConnectionPtr> lists_;
    PollerCallback onConectionCallback_;
    PollerCallback onMessageCallback_;
    PollerCallback onCloseCallback_;
    
    typedef std::map<int, TcpConnectionPtr>::iterator TcpConnectionIterator;
};

#endif /* defined(__Poller__PollPoller__) */
