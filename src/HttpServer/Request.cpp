//
// Created by dominik on 04.11.19.
//
#include <HttpServer/Request.h>

namespace HttpServer
{
    std::string Request::to_str() const
    {
        std::stringstream ss;
        ss << get_request_line()
           << get_header()
           << get_body();
        return ss.str();
    }

    std::string Request::get_request_line() const
    {
        std::stringstream ss;
        ss << request << " " << http_version << "\r\n";
        return ss.str();
    }

    const std::string &Request::get_request() const
    {
        return request;
    }

}
