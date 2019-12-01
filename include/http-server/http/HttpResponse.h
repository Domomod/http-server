//
// Created by dominik on 06.11.19.
//

#ifndef HTTP_SERVER_HTTPRESPONSE_H
#define HTTP_SERVER_HTTPRESPONSE_H

#include <http-server/http/HttpMessage.h>
#include <http-server/http/HttpParser.h>
#include <http-server/http/HttpStatusCodes.h>

/* @brief Http response representation.
 * @details This class allows for represenation of a http/1.1 response.\n
 *          Because the header keys may vary from response to response, this class stores header keys and\n
 *          vectors of coresponding values in a dictionary. Both values and keys are stored as strings.\n
 *          Conversion of those values is left to the class user.\n
 */
class HttpResponse : public HttpMessage
{
public:
    HttpResponse()
    = default;

    void print() const override;

    void print(std::ostream & ss) const override;

private:
    void printResponseLine(std::ostream & os = std::cout) const;

    StatusCode status_code;

    friend class HttpResponseBuilder;
};
#endif //HTTP_SERVER_HTTPRESPONSE_H
