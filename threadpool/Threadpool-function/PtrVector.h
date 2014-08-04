//
//  PtrVector.h
//  Threadpool
//
//  Created by 陈希 on 14-8-4.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Threadpool_PtrVector_h
#define Threadpool_PtrVector_h

#include "NonCopyable.h"
#include <vector>

template <typename T>
class PtrVector: public std::vector<T*>,private NonCopyable
{
public:
    ~PtrVector()
    {
        clear();
    }
    void push_back(T *val)
    {
        std::vector<T*>::push_back(val);
    }
    void clear()
    {
        typename std::vector<T*>::iterator it;
        for (it = std::vector<T*>::begin(); it != std::vector<T*>::end(); it++) {
            delete *it;
        }
        std::vector<T*>::clear();
    }
};

#endif
