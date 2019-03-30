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