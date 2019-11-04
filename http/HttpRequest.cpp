//
// Created by dominik on 04.11.19.
//

#include "HttpRequest.h"
/*!
 * @return type of http request eg GET, PUT ...
 */
const std::string &HttpRequest::getRequest_type() const
{
    return request_type;
}

/*!
 * @return file path or '\' if no file was specified
 */
const std::string &HttpRequest::getPath() const
{
    return path;
}

/*!
 * @return string like HTTP/<DIGIT>+.<DIGIT>+
 */
const std::string &HttpRequest::getHttp_version() const
{
    return http_version;
}

/*!
 * @return body of the request
 */
const std::string &HttpRequest::getBody() const
{
    return body;
}

/*!
 * @brief Looks fo the value of a given header key. Returns an empty vector if no value was specified by the request.
 * If wrong key was given returns only one string "Wrong key".
 * @param field_name Header key to be extracted
 * @return A vector of values as strings.
 */
const std::vector<std::string> HttpRequest::getFieldValue(const std::string &field_name)
{
    auto search = header_info.find(field_name);
    if (search != header_info.end())
    {
        return search->second;
    }
    else
    {
        return std::vector<std::string>({"Wrong key"});
    }
}

