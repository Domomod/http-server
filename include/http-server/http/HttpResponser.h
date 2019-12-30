//
// Created by Julia on 2019-12-30.
//

#ifndef HTTP_SERVER_HTTPRESPONSER_H
#define HTTP_SERVER_HTTPRESPONSER_H

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpResponseBuilder.h"
#include "../Building/BuildingSystem.h"
#include <memory>

class HttpResponser {
private:
    std::shared_ptr<BuildingSystem> buildingSystem;
    HttpResponseBuilder responseBuilder;
public:
    HttpResponse createResponse(std::shared_ptr<HttpRequest> request);
    HttpResponser(std::shared_ptr<BuildingSystem> building);
};


#endif //HTTP_SERVER_HTTPRESPONSER_H
