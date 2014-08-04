//
//  NonCopyable.h
//  Threadpool
//
//  Created by 陈希 on 14-8-4.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Threadpool_NonCopyable_h
#define Threadpool_NonCopyable_h

class NonCopyable
{
public:
    NonCopyable() {}
    ~NonCopyable() {}
private:
    NonCopyable(const NonCopyable &);
    void operator=(const NonCopyable &);
};

#endif
