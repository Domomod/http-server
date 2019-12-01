//
// Created by dominik on 23.11.19.
//

#include <http-server/http/HttpMessage.h>
const std::string HttpMessage::NO_SUCH_KEY = "No such key";


const std::string &HttpMessage::getHttp_version() const
{
    return http_version;
}


const std::string &HttpMessage::getBody() const
{
    return body;
}


const std::vector<std::string> HttpMessage::getFieldValue(const std::string &field_name)
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


void HttpMessage::printHeader(std::ostream & os) const
{
    for (const auto & elem :header_info)
    {
        os << elem.first << ": ";
        bool is_not_first_val = false;
        for (const auto & val : elem.second)
        {
            if(is_not_first_val)
            {
                os << ", ";
            }
            os << val;
            is_not_first_val = true;
        }
        os << "\r\n";
    }
    os << "\r\n";
}


void HttpMessage::printBody(std::ostream & os) const
{
    os << body;
}