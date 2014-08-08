//
//  NonCopyable.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Poll_NonCopyable_h
#define Poll_NonCopyable_h

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
