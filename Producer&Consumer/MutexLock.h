//
//  MutexLock.h
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Producer_Consumer_MutexLock_h
#define Producer_Consumer_MutexLock_h
#include <pthread.h>
#include <stdexcept>

class MutexLock
{
public:
    MutexLock()
    {
        if(pthread_mutex_init(&lock_, NULL)){
            throw std::runtime_error("init lock fail!");
        }
    }
    
    ~MutexLock()
    {
        if(pthread_mutex_destroy(&lock_)){
            throw std::runtime_error("destroy lock fail");
        }
    }
    
    void lock(){
        if(pthread_mutex_lock(&lock_)){
            throw std::runtime_error("lock failed!");
        }
    }
    
    void unlock(){
        if(pthread_mutex_unlock(&lock_)){
            throw std::runtime_error("unlock failed!");
        }
    }
    
    //这里提供指针是为了cond的wait操作
    //这里不能为const
    pthread_mutex_t *getMutexLockPtr()
    {
        return &lock_;
    }
    
private:
    pthread_mutex_t lock_;
};

#endif  /*MUTEX_LOCK_H_*/




