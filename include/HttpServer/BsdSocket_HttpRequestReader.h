//
// Created by dominik on 22.11.19.
//

#ifndef HTTP_SERVER_BSDSOCKET_HTTPREQUESTREADER_H
#define HTTP_SERVER_BSDSOCKET_HTTPREQUESTREADER_H

#include <HttpServer/HttpRequestReader.h>
#include <HttpServer/HttpRequest.h>

class BsdSocket_HttpRequestReader : public HttpRequestReader
{
public:
    BsdSocket_HttpRequestReader(int connection_socket_descriptor);

    ~BsdSocket_HttpRequestReader() override;;

    HttpRequest get_request() override;

private:
    inline bool contains(const std::__cxx11::string &line, char character);
    std::__cxx11::string extractLine(std::__cxx11::string& str);
    std::__cxx11::string splitOnNth(std::__cxx11::string &str, unsigned long  n);

    int connection_socket_descriptor;
    char buf[101];
    std::__cxx11::string unprocessed_data;
};


#endif //HTTP_SERVER_BSDSOCKET_HTTPREQUESTREADER_H
