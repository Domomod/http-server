//
// Created by dominik on 18.12.19.
//

#ifndef HTTP_SERVER_CLIENTERROR_H
#define HTTP_SERVER_CLIENTERROR_H

#include <http-server/http/exceptions/HttpException.h>

/*!
 * @brief Indicates that client's request cannot be performed, because of an error made by the client.
 */
class ClientError : public HttpException
{

};

#endif //HTTP_SERVER_CLIENTERROR_H
