#ifndef _HANDLE_HPP_
#define _HANDLE_HPP_

class Animal;

class Handle
{
    public:
        Handle();
        Handle(const Animal *);
        Handle(const Handle &);
        Handle &operator=(const Handle &);
        ~Handle();

        Animal *operator->();
        const Animal *operator->() const;

    private:
        Animal *ptr_;
};

#endif /*_HANDLE_HPP_*/