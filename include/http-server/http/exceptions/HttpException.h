//
// Created by dominik on 18.12.19.
//

#ifndef HTTP_SERVER_HTTPEXCEPTIONS_H
#define HTTP_SERVER_HTTPEXCEPTIONS_H

#include <utility>
#include <exception>
#include <string>
#include <http-server/http/exceptions/HttpStatusCodes.h>

class HttpException : public std::exception
{
public:
    HttpException(StatusCode StatusCode, std::string msg = "") : statusCode(StatusCode), msg(std::move(msg))
    {
    }

private:
    const char* what() const noexcept override
    {
        return msg.c_str();
    };

protected:
    StatusCode statusCode;
    std::string msg;
};

#endif //HTTP_SERVER_HTTPEXCEPTIONS_H
