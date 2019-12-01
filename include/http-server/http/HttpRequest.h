//
// Created by dominik on 04.11.19.
//

#ifndef HTTP_SERVER_HTTPREQUEST_H
#define HTTP_SERVER_HTTPREQUEST_H

#include <string>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <iostream>
#include <http-server/http/HttpMessage.h>

class HttpRequest;


/*!
 * @brief Http request representation.
 * @details This class allows for represenation of a http/1.1 request.\n
 *          Because the header keys may vary from request to request, this class stores header keys and\n
 *          vectors of coresponding values in a dictionary. Both values and keys are stored as strings.\n
 *          Conversion of those values is left to the class user.\n
 */
class HttpRequest : public HttpMessage
{
public:
    /*!
     * @brief Simple getter.
     * @return Request type aka. GET,PUT,etc...
     */
    const std::string &getRequest_type() const;

    /*!
     * @brief Simple getter.
     * @return Path to the requested file
     */
    const std::string &getPath() const;

    void print() const override;

    /*!
     * @brief Prints the request in human readable way on the standard output;
     */
    void print(std::ostream & ss) const override;
private:
    void printRequestLine(std::ostream & = std::cout) const;

    HttpRequest()
    = default;

    std::string request_type;
    std::string path;

    friend class HttpParser;
};


#endif //HTTP_SERVER_HTTPREQUEST_H
