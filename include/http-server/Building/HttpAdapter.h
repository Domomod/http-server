//
// Created by Julia on 2019-12-30.
//

#ifndef HTTP_SERVER_HTTPRESPONSER_H
#define HTTP_SERVER_HTTPRESPONSER_H

#include "http-server/http/HttpResponse.h"
#include "http-server/http/HttpRequest.h"
#include "http-server/http/HttpResponseBuilder.h"
#include "http-server/Building/BuildingSystem.h"
#include <memory>
#include <boost/xpressive/xpressive.hpp>

using boost::xpressive::sregex;

class HttpResponser {
private:
    std::shared_ptr<BuildingSystem> buildingSystem;
    HttpResponseBuilder responseBuilder;
    sregex get_regex;
    sregex post_regex;
    sregex put_regex;
    sregex destination_regex;
    sregex delete_regex;
public:
    HttpResponse createResponse(std::shared_ptr<HttpRequest> request);
    HttpResponser(std::shared_ptr<BuildingSystem> building);
};


#endif //HTTP_SERVER_HTTPRESPONSER_H
