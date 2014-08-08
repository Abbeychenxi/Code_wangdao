//
//  Timer.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__Timer__
#define __Poll__Timer__

#include <iostream>
#include "NonCopyable.h"
#include <functional>
#include <sys/timerfd.h>

class Timer : NonCopyable
{
public:
    typedef std::function<void()> TimeCallback;
    Timer();
    ~Timer();
    
    void setTimer(int val, int interval);
    void setTimerCallback(const TimeCallback &);
    void runTimer();
    void cancelTimer();
    
private:
    int timerfd_;
    struct itimerspec howlong_;
    TimeCallback timeCallback_; //用户逻辑
    bool isStarted_;  //是否开启
};


#endif /* defined(__Poll__Timer__) */
