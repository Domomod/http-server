//
// Created by dominik on 30.11.19.
//

#include <http-server/http/HttpResponseBuilder.h>

HttpResponseBuilder::HttpResponseBuilder()
{
    init();
}

void HttpResponseBuilder::init()
{
    httpResponse = new HttpResponse;
    httpResponse->http_version = "HTTP/1.1";
}

HttpResponseBuilder &
HttpResponseBuilder::setHeaderInfo(const std::map<std::__cxx11::string, std::vector<std::__cxx11::string>> &dictionary)
{
    httpResponse->header_info.insert(dictionary.begin(), dictionary.end());
    return *this;
}

HttpResponseBuilder & HttpResponseBuilder::set_status_code(StatusCode statusCode)
{
    httpResponse->status_code = statusCode;
    isStatusCodeSet = true;
    return *this;
}

HttpResponseBuilder & HttpResponseBuilder::set_body(std::string body)
{
    httpResponse->body = body;
    httpResponse->addFieldValue("Content-Length", {std::to_string(body.size())});
    return *this;
}

HttpResponse HttpResponseBuilder::getResponse()
{
    if (isStatusCodeSet)
    {
        HttpResponse response = *httpResponse;
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
