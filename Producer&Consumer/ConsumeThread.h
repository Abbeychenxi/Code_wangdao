//
//  ConsumeThread.h
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Producer_Consumer_ConsumeThread_h
#define Producer_Consumer_ConsumeThread_h
#include <pthread.h>

class Buffer;

class ConsumeThread
{
public:
    ConsumeThread(Buffer &buffer);
    
    
    void start();
    static void *threadFunc(void *arg);
    void run();
    void join();
    
    
private:
    pthread_t tid_;
    Buffer &buffer_;
    int j_;
};


#endif
