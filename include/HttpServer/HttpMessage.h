//
// Created by dominik on 23.11.19.
//

#ifndef HTTP_SERVER_HTTPMESSAGE_H
#define HTTP_SERVER_HTTPMESSAGE_H

#include <string>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <iostream>
#include <HttpServer/HttpMessage.h>
#include <sstream>

class HttpResponseBuilder;

/*!
 * @brief Abstract base class for HttpRequest and HttpResponse.
 */
class HttpMessage
{
public:
    HttpMessage()
    = default;

    const std::string &get_http_version() const;


    const std::string &get_body() const;

    std::string get_header() const;


    /*!
     * @brief Looks fo the value of a given header key. Returns an empty vector if no value was specified by the request.\n
     * If wrong key was given returns vector containing only NO_SUCH_KEY, which is a string defined inside this class..
     * @param field_name Header key to be extracted
     * @return A vector of header values corresponding to given header key.
     */
    const std::vector<std::string> get_field_value(const std::string &field_name) const;

    virtual std::string to_str() const = 0;

    /*!
     * @brief A string value returned when getFieldValue does not find a field with given name.
     */
    static const std::string NO_SUCH_KEY;
protected:

    /*!
     * @brief Adds or assigns given value to the header dictionary.
     * @param field_name Header field name.
     * @param values A vector of values as strings.
     */
    inline void addFieldValue(const std::string field_name, const std::vector<std::string> & values)
    {
        header_info.insert_or_assign(field_name, values);
    }

    std::string http_version;
    std::map<std::string, std::vector<std::string>> header_info;
    std::string body;
private:
    friend class HttpParser;
    friend class HttpResponseBuilder;
};


#endif //HTTP_SERVER_HTTPMESSAGE_H
