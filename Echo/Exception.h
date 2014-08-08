//
//  Exception.h
//  Poll
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __Poll__Exception__
#define __Poll__Exception__

#include <iostream>
#include <string>
#include <exception>

class Exception: public std::exception
{
public:
    explicit Exception(const char *);
    explicit Exception(const std::string &);
    
    virtual ~Exception() throw();
    virtual const char * what() const throw();
    const char *stackTrace() const throw();
private:
    void fillStackTrace();
    
    std::string message_;
    std::string stack_;
};



#endif /* defined(__Poll__Exception__) */
