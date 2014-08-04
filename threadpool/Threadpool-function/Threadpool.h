//
//  Threadpool.h
//  Threadpool
//
//  Created by 陈希 on 14-8-3.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Threadpool__Threadpool__
#define __Threadpool__Threadpool__

#include "NonCopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include "PtrVector.h"
#include <queue>
#include <functional>
#include <iostream>

class Thread;

class Threadpool: private NonCopyable
{
public:
    typedef std::function<void()> Task;
    
    Threadpool(size_t queueSize, size_t poolSize);
    ~Threadpool();
    
    void start();
    void stop();
    
    void addTask(const Task &);
    Task getTask();
private:
    void runInThread();
    
    mutable MutexLock mutex_;
    Condition empty_;
    Condition full_;
    size_t queueSize_;
    std::queue<Task> queue_;
    size_t poolSize_;
    PtrVector<Thread> threads_;
    bool isStarted_;
};

#endif /* defined(__Threadpool__Threadpool__) */
