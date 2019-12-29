//
// Created by dominik on 18.12.19.
//

#ifndef HTTP_SERVER_HTTPEXCEPTIONS_H
#define HTTP_SERVER_HTTPEXCEPTIONS_H

#include <exception>
#include <string>
#include <http-server/http/HttpStatusCodes.h>


class HttpException : public std::exception
{
    const char* what() const noexcept override = 0;
    virtual const std::string asHttpMessage() = 0;

protected:
    StatusCode StatusCode;
};

#endif //HTTP_SERVER_HTTPEXCEPTIONS_H
