//
//  Queue.h
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Producer_Consumer_Queue_h
#define Producer_Consumer_Queue_h
#include <stddef.h>

//这是队列的结点
class Node{
    friend class Queue;
private:
    int data_;
    Node *next_;
};
typedef Node *NodePtr;


class Queue{
public:
    Queue();
    ~Queue();
    void push(int data);
    void pop();
    int top() const;
    void clear();
    bool isEmpty() const;
    size_t getSize() const;
private:
    NodePtr head_;
    NodePtr tail_;
    size_t size_;
};


#endif
