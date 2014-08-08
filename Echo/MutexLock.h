//
//  MutexLock.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Poll_MutexLock_h
#define Poll_MutexLock_h

#include <pthread.h>
#include <assert.h>
#include "NonCopyable.h"

class MutexLock: NonCopyable
{
    friend class MutexLockGuard;
public:
    MutexLock();
    ~MutexLock();
    
    pthread_mutex_t *getMutexPtr() { return &mutex_; }
    bool isLocked() const { return isLocked_; }
    
private:
    void lock();
    void unlock();
    
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
    isLocked_ = false;
    pthread_mutex_unlock(&mutex_);
}

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex);
    ~MutexLockGuard();
    
private:
    MutexLock &mutex_;
};

inline MutexLockGuard::MutexLockGuard(MutexLock &mutex)
:mutex_(mutex)
{
    mutex_.lock();
}

inline MutexLockGuard::~MutexLockGuard()
{
    mutex_.unlock();
}

#define MutexLockGuard(m) "ERROR"

#endif
