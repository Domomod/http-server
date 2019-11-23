//
// Created by dominik on 22.11.19.
//

#ifndef HTTP_SERVER_BSDSOCKET_HTTPREQUESTREADER_H
#define HTTP_SERVER_BSDSOCKET_HTTPREQUESTREADER_H

#include <http-server/http/HttpRequestReader.h>
#include <http-server/http/HttpRequest.h>

class BsdSocket_HttpRequestReader : public HttpRequestReader
{
public:
    BsdSocket_HttpRequestReader(int connection_socket_descriptor);

    virtual ~BsdSocket_HttpRequestReader();

    HttpRequest getRequest() override;

private:
    inline bool contains(const std::__cxx11::string &line, char character);
    std::__cxx11::string extractLine(std::__cxx11::string& str);
    std::__cxx11::string splitOnNth(std::__cxx11::string &str, unsigned long  n);

    int connection_socket_descriptor;
    char buf[101];
    std::__cxx11::string unprocessed_data;
};


#endif //HTTP_SERVER_BSDSOCKET_HTTPREQUESTREADER_H
