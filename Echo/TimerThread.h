//
//  TimerThread.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__TimerThread__
#define __Poll__TimerThread__

#include <iostream>
#include "NonCopyable.h"
#include "Thread.h"
#include "Timer.h"
#include <functional>


class TimerThread : private NonCopyable
{
public:
    typedef std::function<void()> TimerCallback;
    void setTimer(int value, int interval);
    void setTimerCallback(const TimerCallback &cb);
    void startTimerThread();
    void cancelTimerThread();
    
private:
    Timer timer_;
    Thread thread_;
};
#endif /* defined(__Poll__TimerThread__) */
