#include "Thread.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

class FooThread
{
    public:
        FooThread();
        void print();
        void startTimerThread();
    private:
        Thread thread_;
        Timer timer_;
};

FooThread::FooThread()
{
}

void FooThread::print()
{
    cout << "Hello World" << endl;
}

void FooThread::startTimerThread()
{
    timer_.setTimer(3, 1);
    timer_.setTimeCallback(bind(&FooThread::print, this));
    thread_.setCallback(bind(&Timer::runTimer, &timer_));
    thread_.start();
    thread_.join();
}



int main(int argc, const char *argv[])
{
    FooThread foo;
    foo.startTimerThread();
    return 0;
}
