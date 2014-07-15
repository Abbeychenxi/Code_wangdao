//
//  Workshop.cpp
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "Workshop.h"
#include "Buffer.h"
#include "ProduceThread.h"
#include "ConsumeThread.h"
using namespace std;
Workshop::Workshop(size_t consumer_n,
                   size_t producer_n,
                   size_t size)
:consumer_n_(consumer_n),
producer_n_(producer_n),
buffer_size_(size),
buffer_(buffer_size_),
ProduceThreads_(producer_n_, ProduceThread(buffer_)),
ConsumeThreads_(consumer_n_, ConsumeThread(buffer_))
{
    
}

Workshop::~Workshop()
{
    
}
void Workshop::start()
{
    for (vector<ProduceThread>::iterator it = ProduceThreads_.begin(); it != ProduceThreads_.end(); ++it) {
        it->start();
    }
    for (vector<ConsumeThread>::iterator it = ConsumeThreads_.begin(); it != ConsumeThreads_.end(); ++it) {
        it->start();
    }
    for (vector<ProduceThread>::iterator it = ProduceThreads_.begin(); it != ProduceThreads_.end(); ++it) {
        it->join();
    }
    for (vector<ConsumeThread>::iterator it = ConsumeThreads_.begin(); it != ConsumeThreads_.end(); ++it) {
        it->join();
    }
}