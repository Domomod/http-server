//
// Created by dominik on 04.11.19.
//

#include "HttpRequest.h"

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
        return std::vector<std::string>();
    }
}

