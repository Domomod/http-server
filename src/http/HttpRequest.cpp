//
// Created by dominik on 04.11.19.
//
#include <http-server/http/HttpRequest.h>

const std::string HttpRequest::NO_SUCH_KEY = "No such key";

const std::string &HttpRequest::getRequest_type() const
{
    return request_type;
}


const std::string &HttpRequest::getPath() const
{
    return path;
}

const std::string &HttpRequest::getHttp_version() const
{
    return http_version;
}


const std::string &HttpRequest::getBody() const
{
    return body;
}


const std::vector<std::string> HttpRequest::getFieldValue(const std::string &field_name)
{
    auto search = header_info.find(field_name);
    if (search != header_info.end())
    {
        return search->second;
    }
    else
    {
        return std::vector<std::string>({"No such header"});
    }
}

void HttpRequest::print() const
{
    std::cout << "Type:\t" << request_type
              << "\nPath:\t" << path
              << "\nHttp version:\t" << http_version << "\n";
    for (auto elem :header_info)
    {
        std::cout << elem.first << ":";
        for (auto val : elem.second)
        {
            std::cout << "\n\t" << val;
        }
        std::cout << "\n";
    }
    std::cout << body << "\n";
}

