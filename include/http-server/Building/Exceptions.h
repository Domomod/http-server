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


DEFINE_EXCEPTION(MethodNotImplemented, "This method is not implemented.");


#undef DEFINE_EXCEPTION

#endif //HTTP_SERVER_EXCEPTIONS_H

/*
{   throw MethodNotImplemented();   }
*/
