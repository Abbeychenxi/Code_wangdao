//
//  queue.cpp
//  threadpool
//
//  Created by 陈希 on 14-7-28.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "def.h"
#include <iostream>
#include <string>
using namespace std;
queue::queue()
:head_(NULL),tail_(NULL),size_(0)
{
    
}

void queue::queue_push(task data)
{
    NODE* pt = (NODE*)malloc(sizeof(NODE));
    pt->data_ = data;
    pt->next_ = NULL;
    if (is_queue_empty()) {
        head_ = tail_ = pt;
    }else {
        tail_->next_ = pt;
        tail_ = pt;
    }
    ++size_;
}

void queue::queue_pop() {
    NODE* pt = head_;
    head_ = head_->next_;
    delete pt;
    --size_;
}

task queue::queue_top() {
    if (is_queue_empty()) {
        cout << "queue empty" << endl;
        exit(EXIT_FAILURE);
    }
    return head_->data_;
}

void queue::queue_clear() {
    while (!is_queue_empty()) {
        queue_pop();
    }
}

int queue::is_queue_empty() {
    return head_ == NULL;
}

size_t queue::get_queue_size() {
    return size_;
}
