//
//  Condition.h
//  Threadpool
//
//  Created by 陈希 on 14-8-4.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Threadpool__Condition__
#define __Threadpool__Condition__

#include <iostream>
#include <pthread.h>
#include "NonCopyable.h"

class MutexLock;

class Condition: private NonCopyable
{
public:
    Condition(MutexLock &mutex);
    ~Condition();
    
    void wait();
    void notify();
    void notifyAll();
    
private:
    pthread_cond_t cond_;
    MutexLock &mutex_;
};

#endif /* defined(__Threadpool__Condition__) */
