//
// Created by dominik on 05.01.20.
//

#ifndef HTTP_SERVER_EXCEPTIONS_H
#define HTTP_SERVER_EXCEPTIONS_H

#include <exception>

#define DEFINE_EXCEPTION(ClassName, msg)\
class ClassName : public std::exception\
{\
public:\
ClassName()\
{}\
const char *what()\
{\
    return msg;\
}}

namespace BuildingSystem
{
    DEFINE_EXCEPTION(MethodNotImplemented, "This method is not supported by at least one of the resources.");

    DEFINE_EXCEPTION(ResourceNotFound, "Resource not found.\n");

    DEFINE_EXCEPTION(ResourceAlreadyExists, "Resource already exists.\n");

    DEFINE_EXCEPTION(UnfittingComponentGiven, "Provided object does not fit it's destination.\n");

    DEFINE_EXCEPTION(UnbalancedCompositeGiven, "Provided object does not fit it's destination.\n");

    DEFINE_EXCEPTION(SourceIsDestination, "Destination need's to be diffrent than source.\n");
}

#undef DEFINE_EXCEPTION

#endif //HTTP_SERVER_EXCEPTIONS_H