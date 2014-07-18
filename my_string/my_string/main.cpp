//
//  main.cpp
//  my_string
//
//  Created by 陈希 on 14-7-18.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include <iostream>
#include "my_string.h"

int main(int argc, const char * argv[])
{

    // insert code here...
    String s1="宿青牛逼";
    s1.debug();
    String s2 = "真牛逼";
    s2.debug();
    String s = s1 + s2;
    s.debug();
    
    return 0;
}

