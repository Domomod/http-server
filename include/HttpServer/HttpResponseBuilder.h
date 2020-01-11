//
// Created by dominik on 30.11.19.
//

#ifndef HTTP_SERVER_HTTPRESPONSEBUILDER_H
#define HTTP_SERVER_HTTPRESPONSEBUILDER_H

#include <HttpServer/HttpResponse.h>
#include <HttpServer/HttpStatusCodes.h>

/*!
 * @brief A fancier version of a builder pattern, allowing for cascade calls of it's methods. Build a HttpResponse.
 * Absoulte minimum to create a HttpResponse is to set it's StatusCode. Does not remember values of HttpRequest after
 * returning it to the user.
 */
class HttpResponseBuilder
{
public:
    HttpResponseBuilder();

    HttpResponseBuilder & set_status_code(StatusCode statusCode);

    /*!
     * @brief Adds multiple headers th the response.
     * @param dictionary A dictionary of header names and values.
     * @return Reference to the HttpResponseBuilder for cascade calls of it's methods.
     */
    HttpResponseBuilder & setHeaderInfo(
            const std::map<std::__cxx11::string, std::vector<std::__cxx11::string>> &dictionary);

    /*!
     * @brief Adds the body to the response. Also automatically adds the "Content-Length" header value.
     * @param body The body of the response
     * @return Reference to the HttpResponseBuilder for cascade calls of it's methods.
     */
    HttpResponseBuilder & set_body(std::string body);

    /*!
     * @brief Returns the request. Instantly forgets the request, so calling getResponse twice in a row won't return
     * the same response twice. Checks if it contains a status code. If not terminates the program.
     * @return a HttpResponse.
     */
    HttpResponse getResponse();

public:
    bool isStatusCodeSet = false;
    HttpResponse *httpResponse;

    /*!
     * @brief Initialises a new response. Returns the builder to the state after it's construction.
     */
    void init();
};

#endif //HTTP_SERVER_HTTPRESPONSEBUILDER_H
