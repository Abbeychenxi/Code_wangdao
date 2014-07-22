#include "Handle.hpp"
#include "Animal.h"

Handle::Handle()
:ptr_ (NULL)
{

}

Handle::Handle(const Animal *a)
:ptr_(a -> copy())
{

}

Handle::Handle(const Handle &other)
:ptr_(other.ptr_->copy())
{

}

Handle::~Handle()
{
    delete ptr_;
}

Handle &Handle::operator=(const Handle &other)
{
    if (this != &other)
    {
        delete ptr_;
        ptr_ = other.ptr_ -> copy();
    }
    return *this;
}

Animal *Handle::operator->()
{
    return ptr_;
}
const Animal *Handle::operator->() const
{
    return ptr_;
}

int main(int argc, char const *argv[])
{
    Cat c;
    Handle h(&c);
    h->display();

    return 0;
}