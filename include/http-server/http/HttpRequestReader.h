//
// Created by dominik on 22.11.19.
//

#include "HttpRequest.h"
#include "HttpParser.h"

#ifndef HTTP_SERVER_HTTPREQUESTREADER_H
#define HTTP_SERVER_HTTPREQUESTREADER_H


class HttpRequestReader
{
public:
    HttpRequestReader();
    virtual ~HttpRequestReader();

    virtual HttpRequest getRequest() = 0;

protected:
    HttpParser httpParser;
};


#endif //HTTP_SERVER_HTTPREQUESTREADER_H
