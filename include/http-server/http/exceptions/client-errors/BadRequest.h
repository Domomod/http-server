//
// Created by dominik on 18.12.19.
//

#ifndef HTTP_SERVER_BAD_REQUEST_H
#define HTTP_SERVER_BAD_REQUEST_H

#include "ClientError.h"

/*!
 * @brief Used when no other 4XX code is appropiate.
 * For example invalid syntax, invalid parameters etc...
 */
class BadRequest : public ClientError
{
public:
    BadRequest()
    {
        this->StatusCode = StatusCode::Bad_Request;
    }
};

#endif //HTTP_SERVER_BAD_REQUEST_H