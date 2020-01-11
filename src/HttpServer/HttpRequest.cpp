//
// Created by dominik on 04.11.19.
//
#include <HttpServer/HttpRequest.h>


std::string HttpRequest::to_str() const
{
    std::stringstream ss;
    ss << get_request_line()
       << get_header()
       << get_body();
    return ss.str();
}

std::string HttpRequest::get_request_line() const
{
    std::stringstream ss;
    ss << request << " " << http_version << "\r\n";
    return ss.str();
}

const std::string &HttpRequest::get_request() const
{
    return request;
}
