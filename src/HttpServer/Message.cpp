//
// Created by dominik on 23.11.19.
//

#include <HttpServer/Message.h>

namespace HttpServer
{
    const std::string Message::NO_SUCH_KEY = "No such key";


    const std::string &Message::get_http_version() const
    {
        return http_version;
    }


    const std::string &Message::get_body() const
    {
        return body;
    }


    const std::vector<std::string> Message::get_field_value(const std::string &field_name) const
    {
        auto search = header_info.find(field_name);
        if (search != header_info.end())
        {
            return search->second;
        }
        else
        {
            return std::vector<std::string>({NO_SUCH_KEY});
        }
    }


    std::string Message::get_header() const
    {
        std::stringstream ss;
        for (const auto &elem :header_info)
        {
            ss << elem.first << ": ";
            bool is_not_first_val = false;
            for (const auto &val : elem.second)
            {
                if (is_not_first_val)
                {
                    ss << ", ";
                }
                ss << val;
                is_not_first_val = true;
            }
            ss << "\r\n";
        }
        ss << "\r\n";
        return ss.str();
    }
}

