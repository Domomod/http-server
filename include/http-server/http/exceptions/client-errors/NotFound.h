//
// Created by dominik on 18.12.19.
//

#ifndef HTTP_SERVER_NOTFOUND_H
#define HTTP_SERVER_NOTFOUND_H

#include "ClientError.h"


/*!
 * @brief The REST API can’t map the client’s URI to a resource but may be available in the future.
 */
class NotFound : public ClientError
{
public:
    NotFound()
    {
        this->StatusCode = StatusCode::Not_Found;
    }
};

#endif //HTTP_SERVER_NOTFOUND_H
