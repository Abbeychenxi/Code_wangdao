//
//  TcpConnection.h
//  Poller
//
//  Created by 陈希 on 14-8-6.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poller__TcpConnection__
#define __Poller__TcpConnection__

#include "NonCopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "RIO.h"
#include <string>
#include <memory>
#include <functional>
#include <iostream>

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection: private NonCopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;
    
    explicit TcpConnection(int sockfd);
    ~TcpConnection();
    
    int fd() const
    { return sockfd_.fd(); }
    
    ssize_t readn(char *usrbuf, size_t );
    ssize_t readline(char *usrbuf, size_t maxline);
    ssize_t writen(const char *usrbuf, size_t n);
    void send(const std::string &s);
    //std::string receiveString();
    void shutdown();
    
    void setConnectionCallback(const TcpConnectionCallback &cb)
    { onConnectionCallback_ = cb; }
    void setMessageCallback(const TcpConnectionCallback &cb)
    { onMessageCallback_ = cb; }
    void setCloseCallback(const TcpConnectionCallback &cb)
    { onCloseCallback_ = cb; }
    
    void handleConnection()
    { onConnectionCallback_(shared_from_this()); }
    void handleMessage()
    { std::cout << "on TcpConnectionCallback Message" << std::endl;onMessageCallback_(shared_from_this()); }
    void handleClose()
    { onCloseCallback_(shared_from_this()); }
    
private:
    Socket sockfd_;
    Rio buffer_;
    
    TcpConnectionCallback onConnectionCallback_; //连接建立时的回调
    TcpConnectionCallback onMessageCallback_;  //消息到达
    TcpConnectionCallback onCloseCallback_;  //连接关闭
};

#endif /* defined(__Poller__TcpConnection__) */
