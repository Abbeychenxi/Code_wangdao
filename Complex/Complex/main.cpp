//
//  main.cpp
//  Complex
//
//  Created by 陈希 on 14-7-18.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include <iostream>
#include "Complex.h"
using namespace std;
int main(int argc, const char * argv[])
{

    // insert code here...
    Complex c1(1,1);
    Complex c2(1,1);
    
    cout << c1 + c2 << endl;
    
    Complex res;
    res = c1 / c2;
    
    res.debug();
    
    return 0;
}

