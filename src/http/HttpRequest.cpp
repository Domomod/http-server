//
// Created by dominik on 04.11.19.
//
#include <http-server/http/HttpRequest.h>


const std::string &HttpRequest::getRequest_type() const
{
    return request_type;
}

const std::string &HttpRequest::getPath() const
{
    return path;
}

void HttpRequest::print() const
{
    print(std::cout);
}

void HttpRequest::print(std::ostream & ss) const
{
    printRequestLine(ss);
    printHeader(ss);
    printBody(ss);
}

void HttpRequest::printRequestLine(std::ostream & os) const
{
    os << request_type << path << " " << http_version << "\r\n";
}