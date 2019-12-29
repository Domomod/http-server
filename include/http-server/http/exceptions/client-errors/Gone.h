//
// Created by dominik on 18.12.19.
//

#ifndef HTTP_SERVER_GONE_H
#define HTTP_SERVER_GONE_H

#include "ClientError.h"

/*!
 * @brief Indicates that the resource requested by the client has been permanently deleted.
 */
class Gone : public ClientError
{
public:
    Gone()
    {
        this->StatusCode = StatusCode::Gone;
    }
};

#endif //HTTP_SERVER_GONE_H
