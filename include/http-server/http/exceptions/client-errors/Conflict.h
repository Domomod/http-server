//
// Created by dominik on 18.12.19.
//

#ifndef HTTP_SERVER_CONFLICT_H
#define HTTP_SERVER_CONFLICT_H

#include "ClientError.h"

/*!
 * @brief Indicates that a conflict between requests occured.
 */
class Conflict : public ClientError
{
public:
    Conflict()
    {
        this->StatusCode = StatusCode::Conflict;
    }
};

#endif //HTTP_SERVER_CONFLICT_H
