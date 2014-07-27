//
//  def.h
//  threadpool.c
//
//  Created by 陈希 on 14-7-27.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef threadpool_c_def_h
#define threadpool_c_def_h
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

typedef void* (*task_callback)(void *);
typedef struct{
    task_callback task_func_;
    void *arg_;
}task_t;

typedef struct q_node{
    task_t data_;
    struct q_node *next_;
}q_node, *p_node;

typedef struct {
    p_node head_;
    p_node tail_;
    size_t size_;
}Queue;

void queue_init(Queue *Q);
void queue_destroy(Queue *Q);
void queue_push(Queue *Q, task_t data);
void queue_pop(Queue *Q);
task_t queue_top(const Queue *Q);
void queue_clear(Queue *Q);
int is_queue_empty(const Queue *Q);
int get_queue_size(const Queue *Q);

void queue_init(Queue *Q){
    Q->head_ = NULL;
    Q->tail_ = NULL;
    Q->size_ = 0;
}

void queue_destroy(Queue *Q){
    queue_clear(Q);
}


void queue_push(Queue *Q, task_t data){
    p_node pt = (p_node)malloc(sizeof(q_node));
    pt->data_ = data;
    pt->next_ = NULL;
    if(is_queue_empty(Q)){
        Q->head_ = Q->tail_ = pt;
    }else{
        Q->tail_->next_ = pt;
        Q->tail_ = pt;
    }
    ++Q->size_;
}

void queue_pop(Queue *Q){
    p_node pt = Q->head_;
    Q->head_ = Q->head_->next_;
    free(pt);
    --Q->size_;
}

task_t queue_top(const Queue *Q){
    if(is_queue_empty(Q)){
        fprintf(stderr, "queue empty\n");
        exit(EXIT_FAILURE);
    }
    return Q->head_->data_;
}

void queue_clear(Queue *Q){
    while(!is_queue_empty(Q)){
        queue_pop(Q);
    }
}

int is_queue_empty(const Queue *Q){
    return Q->head_ == NULL;
}

int get_queue_size(const Queue *Q){
    return Q->size_;
}

#define ERR_EXIT(m) \
do {\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0);

#define THREAD_POOL_SIZE 5
#define TRUE 1
#define FALSE 0
typedef struct{
    size_t size_;
    pthread_t *threads_;
    int is_start_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
    Queue queue_;
}pool_t;

void thread_pool_init(pool_t *pool, size_t size);
void thread_pool_destroy(pool_t *pool);
void thread_pool_start(pool_t *pool);
void thread_pool_stop(pool_t *pool);
int thread_pool_is_start(const pool_t *pool);
int thread_pool_get_task_queue_size(const pool_t *pool);
void thread_pool_add_task_to_queue(pool_t *pool, task_t task);
int  thread_pool_get_task_from_queue(pool_t *pool, task_t *task);



void thread_pool_init(pool_t *pool, size_t size){
    pool->size_ = size;
    pool->threads_ = (pthread_t *)malloc(pool->size_ * sizeof(pthread_t));
    pthread_mutex_init(&pool->mutex_, NULL);
    pthread_cond_init(&pool->cond_, NULL);
    queue_init(&pool->queue_);
    pool->is_start_ = FALSE;
}
void thread_pool_destroy(pool_t *pool){
    free(pool->threads_);
    thread_pool_stop(pool);
    pthread_mutex_destroy(&pool->mutex_);
    pthread_cond_destroy(&pool->cond_);
    queue_destroy(&pool->queue_);
}
void *thread_pool_func(void *arg){
    pool_t *pool = (pool_t *)arg;
    task_t task;
    while(1){
        int flag = thread_pool_get_task_from_queue(pool, &task);
        if(flag == FALSE){
            break;
        }else{
            task.task_func_(task.arg_);
        }
    }
    return NULL;
}
void thread_pool_start(pool_t *pool){
    if(pool->is_start_ == FALSE){
        pool->is_start_ = TRUE;
        int i;
        for(i = 0; i < pool->size_; ++i){
            pthread_create(&pool->threads_[i], NULL, thread_pool_func, pool);
        }
    }
}
void thread_pool_stop(pool_t *pool){
    if(pool->is_start_ == FALSE){
        return ;
    }
    pool->is_start_ = FALSE;
    pthread_cond_broadcast(&pool->cond_);
    int i;
    for(i = 0; i < pool->size_; ++i){
        pthread_join(pool->threads_[i], NULL);
    }
    queue_clear(&pool->queue_);
}
int thread_pool_is_start(const pool_t *pool){
    return pool->is_start_;
}
int thread_pool_get_task_queue_size(const pool_t *pool){
    return get_queue_size(&pool->queue_);
}

void thread_pool_add_task_to_queue(pool_t *pool, task_t task){
    pthread_mutex_lock(&pool->mutex_);
    if(pool->is_start_){
        queue_push(&pool->queue_, task);
        pthread_cond_signal(&pool->cond_);
    }
    pthread_mutex_unlock(&pool->mutex_);
}
int  thread_pool_get_task_from_queue(pool_t *pool, task_t *task){
    pthread_mutex_lock(&pool->mutex_);
    while(is_queue_empty(&pool->queue_) && pool->is_start_ == TRUE){
        pthread_cond_wait(&pool->cond_, &pool->mutex_);
    }
    if(pool->is_start_ == FALSE){
        pthread_mutex_unlock(&pool->mutex_);
        return FALSE;
    }
    *task = queue_top(&pool->queue_);
    queue_pop(&pool->queue_);
    pthread_mutex_unlock(&pool->mutex_);
    
    return TRUE;
}

void *compute(void *arg){
    int num = (int)arg;
    printf("pricess a number: %d\n", num);
    
    return NULL;
}


#endif
