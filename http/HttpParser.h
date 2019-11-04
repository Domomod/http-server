//
// Created by dominik on 04.11.19.
//

#ifndef HTTP_SERVER_HTTTPPARSER_H
#define HTTP_SERVER_HTTTPPARSER_H

#include "HttpRequest.h"

class HttpParser
{
public:
    HttpRequest static parse_message(const std::__cxx11::string &message);

    static void parse_request_type(HttpRequest &httpRequest, std::__cxx11::string &line);

    static void parse_keys_and_values(HttpRequest &httpRequest, std::__cxx11::string &line);
};

#include <string>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <iostream>

#endif //HTTP_SERVER_HTTTPPARSER_H
