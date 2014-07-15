//
//  ConsumeThread.cpp
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//


#include "ConsumeThread.h"
#include "Buffer.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

ConsumeThread::ConsumeThread(Buffer &buffer)
:tid_(0), buffer_(buffer)
{
    
}

void ConsumeThread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void *ConsumeThread::threadFunc(void *arg)
{
    ConsumeThread *pt = static_cast<ConsumeThread *>(arg);
    pt->run();
    
    return NULL;
}


void ConsumeThread::run()
{
    while(1)
    {
        int data = buffer_.consume();
        cout <<"consume a data " << data << endl;
        sleep(5);
    }
}

void ConsumeThread::join()
{
    pthread_join(tid_, NULL);
}