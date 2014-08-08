//
//  TextQuery.h
//  TextQuery
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#ifndef __TextQuery__TextQuery__
#define __TextQuery__TextQuery__

#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <vector>
#include <map>
#include <set>



class TextQuery {
public:
    typedef std::vector<std::string>::size_type line_no;
    
    TextQuery();
    void read_file()
    { store_file(); build_map(); }
    std::set<line_no> run_query(const std::string&) const;
    std::string text_line(line_no) const;
    std::ifstream& open_file(const std::string &file);
    std::string make_plural(size_t ctr, const std::string &word, const std::string &ending) {
        return (ctr == 1) ? word: word + ending;
    }
    
    void print_result(const std::set<TextQuery::line_no>& locs, const std::string& sought, const TextQuery &file);
private:
    void store_file();
    void build_map();
    std::vector<std::string> lines_of_text;
    std::map<std::string, std::set<line_no> > word_map;
    
    std::set<TextQuery::line_no>;
    std::ifstream is_;
};

#endif /* defined(__TextQuery__TextQuery__) */
