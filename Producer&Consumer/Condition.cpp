//
//  Condition.cpp
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "Condition.h"
#include "MutexLock.h"
#include <stdexcept>

using namespace std;

Condition::Condition(MutexLock &lock)
:lock_(lock)
{
    if(pthread_cond_init(&cond_, NULL)){
        throw std::runtime_error("init cond error");
    }
}

Condition::~Condition()
{
    if(pthread_cond_destroy(&cond_)){
        throw std::runtime_error("destroy cond error");
    }
}


void Condition::wait()
{
    if(pthread_cond_wait(&cond_, lock_.getMutexLockPtr()))
    {
        throw std::runtime_error("wait cond error");
    }
}

void Condition::notify()
{
    if(pthread_cond_signal(&cond_)){
        throw std::runtime_error("signal error");
    }
}
void Condition::notifyAll()
{
    if(pthread_cond_broadcast(&cond_)){
        throw std::runtime_error("broadcast error");
    }
}
