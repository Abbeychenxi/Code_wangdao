//
//  Threadpool.cpp
//  Threadpool
//
//  Created by 陈希 on 14-8-3.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "Threadpool.h"
#include "Thread.h"

using namespace std;

Threadpool::Threadpool(size_t queueSize, size_t poolSize)
:empty_(mutex_),
full_(mutex_),
queueSize_(queueSize),
poolSize_(poolSize),
isStarted_(false)
{
    
}

Threadpool::~Threadpool()
{
    if (isStarted_) {
        stop();
    }
}

void Threadpool::addTask(const Task &task)
{
    mutex_.lock();
    while (queue_.size() >= queueSize_) {
        empty_.wait();
    }
    queue_.push(task);
    full_.notify();
    mutex_.unlock();
}

Threadpool::Task Threadpool::getTask()
{
    mutex_.lock();
    while (queue_.empty() && isStarted_) {
        full_.wait();
    }
    
    Task task;
    if (!queue_.empty()) {
        task = queue_.front();
        queue_.pop();
        empty_.notify();
    }
    mutex_.unlock();
    return task;
}

void Threadpool::runInThread()
{
    while (isStarted_) {
        Task task(getTask());
        if (task) {
            task();
        }
    }
}

void Threadpool::start()
{
    if (isStarted_) {
        return;
    }
    isStarted_ = true;
    for (size_t i = 0; i != poolSize_; ++i) {
        threads_.push_back(new Thread(bind(&Threadpool::runInThread, this)));
    }
    for (size_t i = 0; i != poolSize_; ++i) {
        threads_[i]->start();
    }
}

void Threadpool::stop()
{
    if (isStarted_ == false) {
        return;
    }
    mutex_.lock();
    isStarted_ = false;
    full_.notifyAll();
    mutex_.unlock();
    
    for (size_t i=0; i!=poolSize_; ++i) {
        threads_[i]->join();
    }
    while (!queue_.empty()) {
        queue_.pop();
    }
}