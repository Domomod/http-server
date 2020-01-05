//
// Created by Julia on 2019-12-30.
//

#ifndef HTTP_SERVER_HTTPRESPONSER_H
#define HTTP_SERVER_HTTPRESPONSER_H

#include <http-server/http/HttpResponse.h>
#include <http-server/http/HttpRequest.h>
#include <http-server/http/HttpResponseBuilder.h>
#include <http-server/http/HttpRequestReader.h>
#include <http-server/bsd/BsdSocket_HttpRequestReader.h>

#include "BuildingSystem.h"
#include <memory>
#include <boost/xpressive/xpressive.hpp>

using boost::xpressive::sregex;
using boost::xpressive::smatch;

class HttpAdapter {
private:
    BuildingSystem& buildingSystem;
    HttpResponseBuilder responseBuilder;
    sregex get_regex;
    sregex post_regex;
    sregex put_regex;
    sregex destination_regex;
    sregex delete_regex;
public:
    HttpAdapter(BuildingSystem &buildingSystem);

    void operator()(int connection_socket_descriptor);


    HttpResponse respond_to(const HttpRequest &request);

    void respond_to_get(const boost::xpressive::smatch &match_path);

    void respond_to_post(const HttpRequest &request, const std::string &str,
                         const boost::xpressive::smatch &match_path);

    void respond_to_delete(const boost::xpressive::smatch &match_path);

    void respond_to_put(const HttpRequest &request, const boost::xpressive::smatch &match_path);

    int to_int(const smatch &match_path, const std::string &name) const;
};


#endif //HTTP_SERVER_HTTPRESPONSER_H
