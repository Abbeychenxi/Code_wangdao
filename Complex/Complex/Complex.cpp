//
//  Complex.cpp
//  Complex
//
//  Created by 陈希 on 14-7-18.
//  Copyright (c) 2014年 陈希. All rights reserved.
//
#include <iostream>
#include "Complex.h"
void Complex::debug()
{
    std::cout << real_ << "+" << imag_ << "i" << std::endl;
}

Complex Complex::operator+(const Complex &c) const
{
     return Complex(real_+c.real_, imag_+c.imag_);
}

Complex Complex::operator-(const Complex &c) const
{
    return Complex(real_-c.real_, imag_-c.imag_);
}

Complex Complex::operator*(const Complex &c) const
{
    Complex T;
    T.real_ =(real_*c.real_ - imag_*c.imag_);
    T.imag_ = (real_*c.imag_ + imag_*c.real_);
    return T;
}

Complex Complex::operator/(const Complex &temp) const
{
    Complex c;
    c.real_=(real_*temp.real_+imag_*temp.imag_)/(temp.real_*temp.real_+temp.imag_*temp.imag_);
    c.imag_=(real_*temp.imag_*(-1)+imag_*temp.real_)/(temp.real_*temp.real_+temp.imag_*temp.imag_);
    return c;
}

