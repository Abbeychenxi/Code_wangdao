#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include <iostream>

class Animal
{
public:
    virtual ~Animal() {}
    virtual void display() const =0;
    virtual Animal *copy() const =0;
    
};

class Cat : public Animal
{
public:
    virtual void display() const
    {
        std::cout << "Cat" << std::endl;
    }

    virtual Animal *copy() const
    {
        return new Cat(*this);
    }
    
};



#endif _ANIMAL_H_