//
// Created by dominik on 04.11.19.
//

#ifndef HTTP_SERVER_HTTTPPARSER_H
#define HTTP_SERVER_HTTTPPARSER_H

#include <string>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <iostream>

#include <HttpServer/Request.h>
#include "Request.h"

namespace HttpServer
{
    /*!
    * @brief Simple and naive parser of http requets, relies on data being separated by single spaces.
    * Can produce a HttpRequest class from a string.
    * @details
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
    class RequestParser
    {
    public:
        RequestParser();

        void parse_and_update_buffer(std::string & buffer);

        Request get_request();

        bool is_request_ready() const;

        unsigned long how_much_body_left();

        enum class State
        {
            PARSING_HTTP_REQUEST_LINE,
            PARSING_HTTP_HEADER_FIELDS,
            PARSING_HTTP_MESSAGE_BODY,
            HTTP_REQUEST_READY
        };
    private:
        enum class LineType;

        /*!
         * @brief Parses the request line.
         * @param line Line such as GET|PUT|POST|ect. /<filename>?<params> HTTP<digit>+.<digit>+
         */
        void parse_request_line(const std::string &line);

        /*!
         * @brief Parses a line containig header field.
         * @param line line of header key and values separated by single spaces
         */
        void parse_header(const std::string &line);

        /*!
         * @brief Parses a line of the message body.
         * @param line any string
         */
        void append_to_body(const std::string &line);

        /*!
         * @brief Resets HttpParser to the state after it's construction.
         */
        void reset_state();


        inline bool contains(const std::__cxx11::string &line, char character);

        std::string move_line(std::__cxx11::string &str);

        std::string split_on(std::__cxx11::string &str, unsigned long n);

        Request *httpRequest;
        State currentState;
    };
}
#endif //HTTP_SERVER_HTTTPPARSER_H
