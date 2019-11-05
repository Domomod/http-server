//
// Created by dominik on 04.11.19.
//

#ifndef HTTP_SERVER_HTTPREQUEST_H
#define HTTP_SERVER_HTTPREQUEST_H

#include <string>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <iostream>


class HttpRequest;

class HttpRequest
{
public:
    const std::string &getRequest_type() const;

    const std::string &getPath() const;

    const std::string &getHttp_version() const;

    const std::string &getBody() const;

    const std::vector<std::string> getFieldValue(const std::string &field_name);

    void print() const
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
    }

private:
    HttpRequest()
    {
    }


    std::string request_type;
    std::string path;
    std::string http_version;
    std::map<std::string, std::vector<std::string>> header_info;
    std::string body;

    friend class HttpParser;
};


#endif //HTTP_SERVER_HTTPREQUEST_H
