//
//  Workshop.h
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Producer_Consumer__Workshop__
#define __Producer_Consumer__Workshop__

#include <iostream>
#include <vector>
#include "Buffer.h"
#include "ProduceThread.h"
#include "ConsumeThread.h"

class Workshop{
private:
    size_t consumer_n_;
    size_t producer_n_;
    size_t buffer_size_;
    Buffer buffer_;
    std::vector<ProduceThread> ProduceThreads_;
    std::vector<ConsumeThread> ConsumeThreads_;
    
public:
    Workshop(size_t consumer_n, size_t producer_n, size_t size);
    ~Workshop();
    void start();
};
#endif /* defined(__Producer_Consumer__Workshop__) */
