#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <iostream>
#include <stddef.h>
#include <assert.h>



template <class T>
class Node
{
public:
    T data_;
    Node<T> *next_;
};

template <class T>
class Queue
{
public:
    Queue();
    ~Queue();
    void push(const T data);
    T top() const;
    void pop();
    void clear();
    int isEmpty() const;
    size_t getSize() const;
private:
    Node<T> *head_;
    Node<T> *tail_;
    size_t size_;
};

template <class T>
inline Queue<T>::Queue()
:head_(NULL),tail_(NULL),size_(0)
{

}

template <class T>
inline Queue<T>::~Queue()
{
    clear();
}

template <class T>
inline void Queue<T>::push(T data)
{
    Node<T> *pt = new Node<T>;
    pt -> data_ = data;
    pt -> next_ = NULL;
    if (isEmpty())
    {
        head_ = tail_ = pt;
    }else
    {
        tail_ -> next_ =pt;
        tail_ = pt;
    }
    size_++;
}

template <class T>
inline T Queue<T>::top() const
{
    assert(!isEmpty());
    return head_ -> data_;
}

template <class T>
inline void Queue<T>::pop()
{
    assert(!isEmpty());
    Node<T> *pt = head_;
    head_ = head_ -> next_;
    delete(pt);
    size_--;
}

template <class T>
inline void Queue<T>::clear()
{
    while(!isEmpty())
    {
        pop();
    }
}

template <class T>
inline int Queue<T>::isEmpty() const
{
    return head_ == NULL;
}

template <class T>
inline size_t Queue<T>::getSize() const
{
    return size_;
}

#endif /*_QUEUE_H_*/