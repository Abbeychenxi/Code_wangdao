//
//  main.cpp
//  Threadpool
//
//  Created by 陈希 on 14-8-3.
//  Copyright (c) 2014年 陈希. All rights reserved.
//
#include "Threadpool.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void func(int i)
{
    cout << i << endl;
}

int main(int argc, const char * argv[])
{

    Threadpool pool(5, 4);
    pool.start();
    
    srand(1000);
    while (1) {
        pool.addTask(bind(&func, rand()%100));
        sleep(1);
    }
    
    pool.stop();
    
    
    return 0;
}

