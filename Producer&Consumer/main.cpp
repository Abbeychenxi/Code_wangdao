//
//  main.cpp
//  Producer&Consumer
//
//  Created by 陈希 on 14-7-15.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "ProduceThread.h"
#include "ConsumeThread.h"
#include "Buffer.h"
#include "Workshop.h"
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    
    Workshop wk(0, 1, 5);
    wk.start();
    
    
    return 0;
}