#include "Timer.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void func()
{
    printf("foobar .....\n");
}


int main(int argc, const char *argv[])
{
    Timer t;
    t.setTimer(3, 1);
    t.setTimeCallback(func);
    t.runTimer();
    return 0;
}
