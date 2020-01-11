//
// Created by dominik on 22.11.19.
//

#include "HttpRequest.h"
#include "HttpParser.h"

#ifndef HTTP_SERVER_HTTPREQUESTREADER_H
#define HTTP_SERVER_HTTPREQUESTREADER_H

/*!
 * @brief An interface for a class reading HttpRequest as a string, responsible for sending this string to HttpParser,
 * and returning a parsed HttpRequset to the user.
 */
class HttpRequestReader
{
public:
    HttpRequestReader();
    virtual ~HttpRequestReader();

    /*!
     * @brief Reads a single whole HttpRequest string, parses it with HttpParser, and returns HttpRequest to the user.
     * @return
     */
    virtual HttpRequest get_request() = 0;

protected:
    HttpParser httpParser;
};


#endif //HTTP_SERVER_HTTPREQUESTREADER_H
