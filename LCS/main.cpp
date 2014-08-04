//
//  main.c
//  LCS
//
//  Created by 陈希 on 14-8-4.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
std::string X = "abccfg";
std::string Y = "cfg";
using namespace std;
//int LSC(char* X, char* Y, int i, int j)
//{
//    if (i == 0 || j == 0) {
//        return 0;
//    }
//    if (X[i] == Y[j]) {
//        return LSC(X, Y, i-1, j-1) + 1;
//    }else
//    {
//        return LSC(X, Y, i-1, j) > LSC(X, Y, i, j-1) ? LSC(X, Y, i-1, j) : LSC(X, Y, i, j-1);
//    }
//}
int len1 = X.size();
int len2 = Y.size();
int memo[10][10]={0};
int LSC(const string x,const string y)
{
    for (int i = 1; i <= x.size(); ++i) {
        for (int j =1; j <= y.size(); ++j) {
            if (x[i-1]==y[j-1]) {
                memo[i][j] = memo[i-1][j-1]+1;
            }else{
                memo[i][j] = memo[i-1][j] >= memo[i][j-1] ? memo[i-1][j] : memo[i][j-1];
            }
        }
    }
    return memo[len1][len2];
}

int main(int argc, const char * argv[])
{
    
//    int i=strlen(X), j=strlen(Y);
//    int len;
//    len = LSC(X, Y, i, j);
//    printf("%d\n", len);
    int len;
    //len = LSC(X, Y, X.size(), Y.size());
    len = LSC(X, Y);
    std::cout << len << std::endl;
    
    return 0;
}

