//
//  main.cpp
//  TextQuery
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "TextQuery.h"
using namespace std;



int main(int argc, const char * argv[])
{
    TextQuery tq;
    string filename;
    cin >> filename;
    if(!tq.open_file(filename)) {
        cerr << "No input file" << endl;
        return EXIT_FAILURE;
    }
    tq.read_file();
    //tq.debug();
    while (true) {
        cout << "enter word to look for , or q to quit: ";
        string s;
        cin >> s;
        if (!cin || s == "q") {
            break;
        }
        set<TextQuery::line_no> locs = tq.run_query(s);
        tq.print_result(locs, s, tq);
    }
    
    
    return 0;
}