//
//  Complex.h
//  Complex
//
//  Created by 陈希 on 14-7-18.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef Complex_Complex_h
#define Complex_Complex_h
class Complex
{
    friend std::ostream &operator<<(std::ostream &os,const Complex &c);
public:
    Complex()
    {
        real_ = 0;
        imag_ = 0;
    }
    
    Complex(double r, double i)
    :real_(r),imag_(i)
    {
        
    }
    
    ~Complex()
    {
        
    }
    void debug();
    Complex operator+(const Complex &c) const;
    Complex operator-(const Complex &c) const;
    Complex operator*(const Complex &c) const;
    Complex operator/(const Complex &c) const;
   
private:
    double real_;
    double imag_;
};

inline std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    os << c.real_ << "+" << c.imag_ << "i";
    return os;
}


#endif
