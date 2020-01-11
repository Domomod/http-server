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

        bool is_connection_ended() const;

    private:
        int connection_socket_descriptor;
        char buf[101];
        std::__cxx11::string unprocessed_data;
        RequestParser httpParser;
        bool end_connection = true;
    };
}


#endif //HTTP_SERVER_HTTPREQUESTREADER_H
