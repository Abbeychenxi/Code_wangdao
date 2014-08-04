//
//  Thread.h
//  Threadpool
//
//  Created by 陈希 on 14-8-4.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Threadpool__Thread__
#define __Threadpool__Thread__

#include <iostream>
#include "NonCopyable.h"
#include <functional>
#include <pthread.h>

class Thread: private NonCopyable
{
public:
    typedef std::function<void ()> ThreadFunc;
    
    Thread(ThreadFunc callback);
    ~Thread();
    
    void start();
    void join();
    
private:
    static void *threadFunc(void *);
    
    pthread_t tid_;
    bool isStarted_;
    ThreadFunc callback_;
};

#endif /* defined(__Threadpool__Thread__) */
