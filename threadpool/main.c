//
//  main.c
//  threadpool.c
//
//  Created by 陈希 on 14-7-27.
//  Copyright (c) 2014年 陈希. All rights reserved.
//
#include "def.h"

int main(void){
    pool_t pool;
    thread_pool_init(&pool, THREAD_POOL_SIZE);
    thread_pool_start(&pool);
    srand(10086);
    while(1){
        int tmp = rand()%99;
        task_t tsk;
        tsk.task_func_ = compute;
        tsk.arg_ = (void*)tmp;
        thread_pool_add_task_to_queue(&pool, tsk);
        sleep(1);
    }
    thread_pool_stop(&pool);
    thread_pool_destroy(&pool);
    return 0;
}