//
//  TcpServer.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__TcpServer__
#define __Poll__TcpServer__

#include <iostream>
#include "NonCopyable.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "Socket.h"
#include "PollPoller.h"
#include <memory>


class TcpServer : private NonCopyable
{
public:
    typedef TcpConnection::TcpConnectionCallback TcpCallback;
    
    explicit TcpServer(const InetAddress &addr);
    
    void setConnection(const TcpCallback &cb)
    { onConnect_ = cb; }
    void setMessage(const TcpCallback &cb)
    { onMessage_ = cb; }
    void setClose(const TcpCallback &cb)
    { onClose_ = cb; }
    
    void start();
    
private:
    std::unique_ptr<Socket> sock_;
    std::unique_ptr<PollPoller> poller_;
    
    TcpCallback onConnect_;
    TcpCallback onMessage_;
    TcpCallback onClose_;
};


#endif /* defined(__Poll__TcpServer__) */
