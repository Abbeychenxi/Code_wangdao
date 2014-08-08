//
//  ThreadPool.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__ThreadPool__
#define __Poll__ThreadPool__

#include <iostream>
#include "NonCopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>
#include <memory>

class Thread;

class ThreadPool: private NonCopyable
{
public:
    typedef std::function<void ()> Task;
    
    ThreadPool(size_t queueSize, size_t pool);
    ~ThreadPool();
    
    void start();
    void stop();
    
    void addTask(const Task &);
    
private:
    Task getTask();
    void runInThread();
    
    mutable MutexLock mutex_;
    Condition empty_;
    Condition full_;
    size_t queueSize_;
    std::queue<Task> queue_;
    size_t poolSize_;
    std::vector<std::unique_ptr<Thread>> threads_;
    bool isStarted_;
};

#endif /* defined(__Poll__ThreadPool__) */
