//
//  MutexLock.h
//  Threadpool
//
//  Created by 陈希 on 14-8-4.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Threadpool_MutexLock_h
#define Threadpool_MutexLock_h

#include <pthread.h>
#include <assert.h>
#include "NonCopyable.h"

class MutexLock: NonCopyable
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    
    pthread_mutex_t *getMutexPtr() {return &mutex_;}
    bool isLocked() const {return isLocked_;}
    
private:
    pthread_mutex_t mutex_;
    bool isLocked_;
};

inline MutexLock::MutexLock()
:isLocked_(false)
{
    pthread_mutex_init(&mutex_, NULL);
}

inline MutexLock::~MutexLock()
{
    assert(isLocked_ == false);
    pthread_mutex_destroy(&mutex_);
}

inline void MutexLock::lock()
{
    pthread_mutex_lock(&mutex_);
    isLocked_ = true;
}

inline void MutexLock::unlock()
{
    pthread_mutex_unlock(&mutex_);
    isLocked_ = false;
}

#endif
