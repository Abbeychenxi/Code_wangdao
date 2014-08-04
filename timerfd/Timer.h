#ifndef TIMER_H
#define TIMER_H 

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
        void setTimeCallback(const TimeCallback &);
        void runTimer();

    private:
        int timerfd_;
        struct itimerspec howlong_;
        TimeCallback timeCallback_; //用户逻辑
};


#endif  /*TIMER_H*/
