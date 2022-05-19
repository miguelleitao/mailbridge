/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 * 
 * https://github.com/thepieterdc/mailbridge/
 */

#include <sstream>
#include "string_util.h"


std::vector<std::string> split_string(const std::string &input, char delimiter) {
    auto ret = std::vector<std::string>();
    auto input_copy = std::string(input);

    size_t pos = 0;
    std::string token;

    while ((pos = input_copy.find(delimiter)) != std::string::npos) {
        token = input_copy.substr(0, pos);
        ret.push_back(token);
        input_copy.erase(0, pos + 1);
    }
    ret.push_back(input_copy);

    return ret;
}

std::vector<std::string> split_string(const std::string &input, const std::string &delimiter) {
    auto ret = std::vector<std::string>();
    auto input_copy = std::string(input);

    size_t pos = 0;
    std::string token;

    while ((pos = input_copy.find(delimiter)) != std::string::npos) {
        token = input_copy.substr(0, pos);
        ret.push_back(token);
        input_copy.erase(0, pos + delimiter.length());
    }
    ret.push_back(input_copy);

    return ret;
}

// trim from end of string (right)
std::string& rtrim(std::string& s, const char* t) {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
std::string& ltrim(std::string& s, const char* t) {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (right then left)
std::string& trim(std::string& s, const char* t) {
    return ltrim(rtrim(s, t), t);
}



