//
//  TimerThread.cpp
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "TimerThread.h"
using namespace std;

void TimerThread::setTimer(int value, int interval)
{
    timer_.setTimer(value, interval);
}

void TimerThread::setTimerCallback(const TimerCallback &cb)
{
    timer_.setTimerCallback(cb);
    thread_.setCallback(bind(&Timer::runTimer, &timer_));
}

void TimerThread::startTimerThread()
{
    thread_.start();
}


void TimerThread::cancelTimerThread()
{
    timer_.cancelTimer();
    thread_.join();
}
