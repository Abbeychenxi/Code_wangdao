#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
//#include "Buffer.h"

using namespace std;

class Thread
{
public:
    Thread(/*Buffer &buffer*/);
    ~Thread();
    void start();
    void join();
    static void *threadFunc(void *arg);
    virtual void run();

protected:
    pthread_t tid_;
    //Buffer &buffer_;
};

Thread::Thread(/*Buffer &buffer*/)
:tid_(0)/*,buffer_(buffer)*/
{
    ::srand(2500);
}

Thread::~Thread()
{

}

void Thread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}


void *Thread::threadFunc(void *arg)
{
    Thread *pt = static_cast<Thread *>(arg);
    pt -> run();

    return NULL;
}

void Thread::run()
{

}

void Thread::join()
{
    pthread_join(tid_, NULL);
}

class ProduceThread : public Thread
{
public:
    void run();
private:
};

void ProduceThread::run()
{
    while(1)
    {
        //int data = rand() % 1000;
        //cout << "produce a data : " << data << endl;
        //buffer_.produce(data);
        //sleep(3);
        cout << "hello" << endl;
    }
}

class ConsumeThread : public Thread
{
public:
    void run();
private:
};

void ConsumeThread::run()
{
     while(1)
    {
        //int data = buffer_.consume();
        //cout <<"consume a data " << data << endl;
        //sleep(5);
    }
}


int main(int argc, char const *argv[])
{
    ProduceThread p;
    p.start();
    p.join();

    return 0;
}