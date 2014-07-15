//
//  Condition.h
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Producer_Consumer_Condition_h
#define Producer_Consumer_Condition_h

#include <pthread.h>

//condition中仅包含Mutex的引用，所以不需要头文件
class MutexLock;

class Condition
{
public:
    Condition(MutexLock &lock);
    ~Condition();
    void wait();
    void notify();
    void notifyAll();
    
private:
    pthread_cond_t cond_;
    MutexLock &lock_;
};

#endif
