/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 * 
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_UTIL_STRING_UTIL_H
#define MAILBRIDGE_UTIL_STRING_UTIL_H

#include <string>
#include <vector>

/**
 * Splits a string by a given delimiter, by iterating through all characters.
 *
 * @param input the input string to split
 * @param delimiter the delimiter to split on
 * @return the parts of the string
 */
std::vector<std::string> split_string(const std::string &input, char delimiter);

/**
 * Splits a string by a given delimiter.
 *
 * @param input the input string to split
 * @param delimiter the delimiter to split on
 * @return the parts of the string
 */
std::vector<std::string> split_string(const std::string &input, const std::string& delimiter);

static const char* ws = " \t\n\r\v";
std::string& rtrim(std::string&, const char* = ws );
std::string& ltrim(std::string&, const char* = ws );
std::string&  trim(std::string&, const char* = ws );



#endif /* MAILBRIDGE_UTIL_STRING_UTIL_H */



