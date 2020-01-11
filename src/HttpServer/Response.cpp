//
// Created by dominik on 06.11.19.
//

#include <HttpServer/Response.h>

namespace HttpServer
{
    std::string Response::to_str() const
    {
        std::stringstream ss;
        ss << get_response_line();
        ss << get_header();
        ss << get_body();
        return ss.str();
    }

    std::string Response::get_response_line() const
    {
        std::stringstream s;
        s << http_version << " " << static_cast<int>(status_code) << " " << ReasonPhrase(status_code) << "\r\n";
        return s.str();
    }
}