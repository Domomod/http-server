//
// Created by dominik on 22.11.19.
//

#ifndef HTTP_SERVER_HTTPREQUESTREADER_H
#define HTTP_SERVER_HTTPREQUESTREADER_H

#include <HttpServer/SocketReader.h>
#include <HttpServer/RequestParser.h>
#include <HttpServer/Request.h>

namespace HttpServer
{
    class SocketReader
    {
    public:
        SocketReader(int connection_socket_descriptor);

        ~SocketReader();

        Request get_request();

    private:
        inline bool contains(const std::__cxx11::string &line, char character);

        std::__cxx11::string extractLine(std::__cxx11::string &str);

        std::__cxx11::string splitOnNth(std::__cxx11::string &str, unsigned long n);

        int connection_socket_descriptor;
        char buf[101];
        std::__cxx11::string unprocessed_data;
        RequestParser httpParser;
    };
}


#endif //HTTP_SERVER_HTTPREQUESTREADER_H
