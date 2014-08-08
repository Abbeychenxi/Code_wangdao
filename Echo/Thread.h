//
//  Thread.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__Thread__
#define __Poll__Thread__

#include <iostream>
#include "NonCopyable.h"
#include <functional>
#include <pthread.h>

class Thread: private NonCopyable
{
public:
    typedef std::function<void ()> ThreadFunc;
    
    Thread();
    explicit Thread(const ThreadFunc &callback);
    ~Thread();
    
    void setCallback(const ThreadFunc &cb);
    
    void start();
    void join();
    
private:
    static void *threadFunc(void *);
    
    pthread_t tid_;
    bool isStarted_;
    ThreadFunc callback_;
};

#endif /* defined(__Poll__Thread__) */
