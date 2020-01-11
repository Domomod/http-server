//
// Created by dominik on 05.01.20.
//

#ifndef HTTP_SERVER_EXCEPTIONS_H
#define HTTP_SERVER_EXCEPTIONS_H


#include <exception>
#include <HttpServer/StatusCodes.h>

class MyException : public std::exception
{
public:
    HttpServer::StatusCode status_code;
    virtual const char *what() = 0;
};

#define DEFINE_EXCEPTION(ClassName, msg, status)\
class ClassName : public MyException\
{\
public:\
    ClassName()\
    {\
        status_code = status;\
    }\
    const char *what()\
    {\
        return msg;\
    }\
}

namespace BuildingSystem
{
    DEFINE_EXCEPTION(MethodNotImplemented, "This method is not supported by at least one of the resources.",
                     HttpServer::StatusCode::Method_Not_Allowed);

    DEFINE_EXCEPTION(ResourceNotFound, "Resource not found.\n", HttpServer::StatusCode::Not_Found);

    DEFINE_EXCEPTION(ResourceAlreadyExists, "Resource already exists.\n", HttpServer::StatusCode::Conflict);

    DEFINE_EXCEPTION(UnfittingObjectGiven, "This object can't be stored in this resource.\n",
                     HttpServer::StatusCode::Method_Not_Allowed);

    DEFINE_EXCEPTION(IncorrectJson, "Json is illformed.\n",
                     HttpServer::StatusCode::Bad_Request);

    DEFINE_EXCEPTION(IllformedBuildingJsonStructure,
                     "Provided json is syntactically correct, but defies our service logic.\n For example represents a floor containing a buildings or map containing entry with key not matching with stored object id.\n",
                     HttpServer::StatusCode::Unprocessable_Entity);

    DEFINE_EXCEPTION(SourceIsDestination, "Destination and source is the same resource.\n",
                     HttpServer::StatusCode::Method_Not_Allowed);
}

#undef DEFINE_EXCEPTION

#endif //HTTP_SERVER_EXCEPTIONS_H