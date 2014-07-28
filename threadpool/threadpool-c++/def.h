//
//  def.h
//  threadpool
//
//  Created by 陈希 on 14-7-27.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef threadpool_def_h
#define threadpool_def_h
#include <iostream>
#include <string>

#define ERR_EXIT(m) \
do {\
perror(m);\
exit(EXIT_FAILURE);\
}while(0);

#define THREAD_POOL_SIZE 5
#define TRUE 1
#define FALSE 0

typedef void* (*task_callback)(void *);
typedef void* (*pool_callback)(void *);
class task {
    friend class queue;
public:
    void *arg;
    task_callback task_func_;
};
class NODE {
    friend class queue;
public:
    
private:
    task data_;
    NODE* next_;
};
class queue {
    friend class pool;
public:
    queue();
    ~queue(){
        queue_clear();
    };
    void queue_push(task data);
    void queue_pop();
    task queue_top();
    void queue_clear();
    int is_queue_empty();
    size_t get_queue_size();
private:
    NODE* head_;
    NODE* tail_;
    size_t size_;
};

class pool {
public:
    pool(size_t size);
    ~pool();
    void pool_start();
    void pool_stop();
    int pool_is_start();
    size_t pool_get_queue_size();
    void pool_add_task_to_queue(task task);
    int pool_get_task_from_queue(task *task);
    static void *thread_pool_func(void *arg);
private:
    size_t size_;
    pthread_t *threads_;
    int is_start_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
    queue queue_;
};

#endif
