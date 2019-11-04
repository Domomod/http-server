//
// Created by dominik on 04.11.19.
//

#ifndef HTTP_SERVER_HTTTPPARSER_H
#define HTTP_SERVER_HTTTPPARSER_H

#include "HttpRequest.h"

/*!
 * @brief Simple and naive parser of http requets, relies on data being separated by single spaces.
 * Can produce a HttpRequest class from a string.
 * @class
 * <ul>
 *  <li> A static class.
 *  <li> Creating a class instance is forbidden.
 *  <li> Does not remember any state, and can be used by multiple threads at the same time.
 *  <li> Works as a factory of HttpRequest objects.
 *  <li> Parsed request string:
 *      <ul>
 *          <li> must contain only one http request, with the end indicating CR LF CR LF trimmed.
 *          <li> use only single spaces as word's separators.
 *          <li> use CR LF as line's separators.
 *          <li> can't contain the body section.
 *      </ul>
 * </ul>
 * @see HttpRequest
 */
class HttpParser
{
public:
    HttpRequest static parse_message(const std::__cxx11::string &message);

private:
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
