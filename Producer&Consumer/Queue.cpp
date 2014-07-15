//
//  Queue.cpp
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "Queue.h"
#include <assert.h>

Queue::Queue()
:head_(NULL), tail_(NULL), size_(0)
{
}

Queue::~Queue()
{
    clear();
}

void Queue::push(int data){
    NodePtr pt = new Node;
    pt->data_ = data;
    pt->next_ = NULL;
    if(isEmpty()){
        head_ = tail_ = pt;
    }else{
        tail_->next_ = pt;
        tail_ = pt;
    }
    size_++;
}

void Queue::pop(){
    assert(!isEmpty());
    NodePtr pt = head_;
    head_ = head_->next_;
    delete pt;
    size_--;
}

int Queue::top() const{
    assert(!isEmpty());
    return head_->data_;
}

void Queue::clear(){
    while(!isEmpty()){
        pop();
    }
}

bool Queue::isEmpty() const{
    return head_ == NULL;
}

size_t Queue::getSize() const{
    return size_;
}
