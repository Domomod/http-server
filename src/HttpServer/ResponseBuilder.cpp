//
// Created by dominik on 30.11.19.
//

#include <HttpServer/ResponseBuilder.h>

namespace HttpServer
{
    ResponseBuilder::ResponseBuilder()
    {
        init();
    }

    void ResponseBuilder::init()
    {
        httpResponse = new Response;
        httpResponse->http_version = "HTTP/1.1";
    }

    ResponseBuilder &
    ResponseBuilder::setHeaderInfo(
            const std::map<std::__cxx11::string, std::vector<std::__cxx11::string>> &dictionary)
    {
        httpResponse->header_info.insert(dictionary.begin(), dictionary.end());
        return *this;
    }

    ResponseBuilder &ResponseBuilder::set_status_code(StatusCode statusCode)
    {
        httpResponse->status_code = statusCode;
        isStatusCodeSet = true;
        return *this;
    }

    ResponseBuilder &ResponseBuilder::set_body(std::string body)
    {
        httpResponse->body = body;
        httpResponse->addFieldValue("Content-Length", {std::to_string(body.size())});
        return *this;
    }

    Response ResponseBuilder::getResponse()
    {
        if (isStatusCodeSet)
        {
            Response response = *httpResponse;
            init();
            isStatusCodeSet = false;
            return response;
        }
        else
        {
            std::cerr << "HttpResponseBuilder can't produce a HtppResponse without a statusCode specified.";
            exit(-1);
        }

    }
}