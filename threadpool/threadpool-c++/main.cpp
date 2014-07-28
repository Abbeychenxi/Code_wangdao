//
//  main.cpp
//  threadpool
//
//  Created by 陈希 on 14-7-27.
//  Copyright (c) 2014年 陈希. All rights reserved.
//
#include "def.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

void *computer(void *arg) {
    long num = (long)arg;
    cout << "process a number: "<< num << endl;
    
    return NULL;
    
}

int main(int argc, const char * argv[])
{

    // insert code here...
    pool pool(THREAD_POOL_SIZE);
    pool.pool_start();
    srand(10086);
    while (1) {
        int tmp = rand()%99;
        task tsk;
        tsk.task_func_ = computer;
        tsk.arg = (void*)tmp;
        pool.pool_add_task_to_queue(tsk);
        sleep(1);
    }
    pool.pool_stop();
    
    return 0;
}

