//
//  pool.cpp
//  threadpool
//
//  Created by 陈希 on 14-7-28.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "def.h"

pool::pool(size_t size)
{
    size_ = size;
    threads_ = (pthread_t *)malloc(size_ * sizeof(pthread_t));
    pthread_mutex_init(&mutex_, NULL);
    pthread_cond_init(&cond_, NULL);
    queue();
    is_start_ = FALSE;
}

pool::~pool() {
    delete threads_;
    pool_stop();
    pthread_mutex_destroy(&mutex_);
    pthread_cond_destroy(&cond_);
    queue_.~queue();
}


 void* pool::thread_pool_func(void *arg){
    pool* pool = static_cast<class pool*>(arg);
    task task;
    while (1) {
        int flag = pool->pool_get_task_from_queue(&task);
        if (flag == FALSE) {
            break;
        }else{
            task.task_func_(task.arg);
        }
    }
    return NULL;
}

void pool::pool_start() {
    if (is_start_ == FALSE) {
        is_start_ = TRUE;
        int i;
        for (i=0; i<size_; ++i) {
            pthread_create(&threads_[i], NULL, thread_pool_func, this);
        }
    }
}

void pool::pool_stop()
{
    if (is_start_ == FALSE) {
        return ;
    }
    is_start_ = FALSE;
    pthread_cond_broadcast(&cond_);
    int i;
    for (i=0; i<size_; ++i) {
        pthread_join(threads_[i], NULL);
    }
    queue_.queue_clear();
}

int pool::pool_is_start() {
    return is_start_;
}

size_t pool::pool_get_queue_size(){
    return queue_.get_queue_size();
}

void pool::pool_add_task_to_queue(task task) {
    pthread_mutex_lock(&mutex_);
    if (is_start_) {
        queue_.queue_push(task);
        pthread_cond_signal(&cond_);
    }
    pthread_mutex_unlock(&mutex_);
}

int pool::pool_get_task_from_queue(task *task) {
    pthread_mutex_lock(&mutex_);
    while (queue_.is_queue_empty() && is_start_ == TRUE) {
        pthread_cond_wait(&cond_, &mutex_);
    }
    if (is_start_ == FALSE) {
        pthread_mutex_unlock(&mutex_);
        return FALSE;
    }
    *task = queue_.queue_top();
    queue_.queue_pop();
    pthread_mutex_unlock(&mutex_);
    
    return TRUE;
}

