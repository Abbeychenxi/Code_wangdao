//
//  TextQuery.cpp
//  TextQuery
//
//  Created by 陈希 on 14-8-8.
//  Copyright (c) 2014年 陈希. All rights reserved.
//

#include "TextQuery.h"
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
using namespace std;

void TextQuery::store_file()
{
    string textline;
    while (getline(is_, textline)) {
        lines_of_text.push_back(textline);
    }
}

void TextQuery::build_map()
{
    for (line_no line_num = 0; line_num != lines_of_text.size(); ++line_num) {
        istringstream line(lines_of_text[line_num]);
        string word;
        while (line >> word) {
            for(string::iterator it = word.begin(); it != word.end(); ++it) {
                if (isupper(*it))
                    tolower(*it);
                if (ispunct(*it))
                    *it = ' ';
            }
            string::iterator new_end = remove_if(word.begin(), word.end(), bind2nd(equal_to<char>(), ' '));

            word.erase(new_end, word.end());
            word_map[word].insert(line_num);
        }
    }
}

std::set<TextQuery::line_no> TextQuery::run_query(const std::string &query_word) const
{
    map<string, set<line_no> >::const_iterator loc = word_map.find(query_word);
    if (loc == word_map.end()) {
        return std::set<TextQuery::line_no>();
    }else {
        return loc->second;
    }
}


string TextQuery::text_line(line_no line) const
{
    if (line < lines_of_text.size()) {
        return lines_of_text[line];
    }
    throw std::out_of_range("line number out of range");
}

std::ifstream& TextQuery::open_file(const std::string &file)
{
    is_.close();     // close in case it was already open
    is_.clear();     // clear any existing errors
    // if the open fails, the stream will be in an invalid state
    is_.open(file.c_str()); // open the file we were given
    return is_; // condition state is good if open succeeded
}

void TextQuery::print_result(const std::set<TextQuery::line_no>& locs, const std::string& sought, const TextQuery &file)
{
    typedef std::set<TextQuery::line_no> line_nums;
    line_nums::size_type size = locs.size();
    std::cout << "\n" << sought << " occurs" << size << " " << make_plural(size, "time", "s") << std::endl;
    line_nums::const_iterator it = locs.begin();
    for (; it != locs.end(); ++it) {
        std::cout << "\t(line " << (*it) + 1 << ")" << file.text_line(*it) << std::endl;
    }
}

TextQuery::TextQuery()
:is_(NULL)
{
    
}

void TextQuery::debug()
{
    map<string, set<line_no> >::const_iterator loc = word_map.begin();
    for(; loc != word_map.end(); loc++) {
        cout << loc->first << endl;
    }
}