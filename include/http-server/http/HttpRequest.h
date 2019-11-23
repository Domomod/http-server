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


class HttpRequest;


/*!
 * @brief Http request representation.
 * @details This class allows for represenation of a http/1.1 request.\n
 *          Because the header keys may vary from request to request, this class stores header keys and\n
 *          vectors of coresponding values in a dictionary. Both values and keys are stored as strings.\n
 *          Conversion of those values is left to the class user.\n
 */
class HttpRequest
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


    /*!
     * @brief Simple getter.
     * @return Http protocol version
     */
    const std::string &getHttp_version() const;

     /*!
      * @brief Simple getter.
      * @return Http request body
      */
    const std::string &getBody() const;

    /*!
     * @brief Looks fo the value of a given header key. Returns an empty vector if no value was specified by the request.\n
     * If wrong key was given returns vector containing only one string "No such header".
     * @param field_name Header key to be extracted
     * @return A vector of header values corresponding to given header key.
     */
    const std::vector<std::string> getFieldValue(const std::string &field_name);

    void print() const;
    static const std::string NO_SUCH_KEY;
private:
    HttpRequest()
    {
    }


    std::string request_type;
    std::string path;
    std::string http_version;
    std::map<std::string, std::vector<std::string>> header_info;
    std::string body;

    friend class HttpParser;
};


#endif //HTTP_SERVER_HTTPREQUEST_H
