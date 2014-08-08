//
//  TcpConnection.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__TcpConnection__
#define __Poll__TcpConnection__

#include <iostream>
#include "NonCopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Rio.h"
#include <string>
#include <memory>
#include <functional>

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : private NonCopyable,
public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;
    
    TcpConnection(int sockfd,
                  const InetAddress &localAddr,
                  const InetAddress &peerAddr);
    ~TcpConnection();
    
    int fd() const
    { return sockfd_.fd();}
    
    ssize_t readn(char *usrbuf, size_t n);
    ssize_t readLine(char *usrbuf, size_t maxline);
    ssize_t writen(const char *usrbuf, size_t n);
    void send(const std::string &s);
    std::string receive();
    void shutdown();
    
    void setConnectionCallback(const TcpConnectionCallback &cb)
    { onConnectionCallback_ = cb; }
    void setMessageCallback(const TcpConnectionCallback &cb)
    { onMessageCallback_ = cb; }
    void setCloseCallback(const TcpConnectionCallback &cb)
    { onCloseCallback_ = cb; }
    
    void handleConnection();
    void handleMessage();
    void handleClose();
    
    const InetAddress &getLocalAddr() const
    { return localAddr_; }
    const InetAddress &getPeerAddr() const
    { return peerAddr_; }
    
    
private:
    Socket sockfd_;  //fd
    Rio buffer_;     //该连接的读写缓冲区
    
    const InetAddress localAddr_;  //Local
    const InetAddress peerAddr_;   //Peer
    
    TcpConnectionCallback onConnectionCallback_; //连接建立时的回调
    TcpConnectionCallback onMessageCallback_;  //消息到达
    TcpConnectionCallback onCloseCallback_;  //连接关闭
};

#endif /* defined(__Poll__TcpConnection__) */
