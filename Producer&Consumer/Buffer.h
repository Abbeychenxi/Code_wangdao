//
//  Buffer.h
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Producer_Consumer_Buffer_h
#define Producer_Consumer_Buffer_h

#include "Queue.h"
#include "MutexLock.h"
#include "Condition.h"

class Buffer{
public:
    Buffer(size_t size);
    ~Buffer();
    
    bool isEmpty() const;
    bool isFull() const;
    
    void produce(int data);
    int consume();
private:
    Queue queue_;
    /*
     * mutable代表在const函数中仍可以被修改
     */
    mutable MutexLock mutex_;
    Condition full_;
    Condition empty_;
    size_t size_;
};

#endif
