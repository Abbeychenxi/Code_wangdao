#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stddef.h>

typedef struct q_node{
    int data_;
    struct q_node *next_;
}q_node, *p_node;

typedef struct{
    p_node head_;
    p_node tail_;
    size_t size_;
}Queue;

void queue_init(Queue *Q);
void queue_destroy(Queue *Q);
void queue_push(Queue *Q, int data);
int queue_top(const Queue *Q);
void queue_pop(Queue *Q);
void queue_clear(Queue *Q);
int queue_is_empty(const Queue *Q);
int queue_get_size(const Queue *Q);

#endif /*QUEUE_H_*/
