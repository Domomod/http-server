//
// Created by dominik on 06.11.19.
//

#include <http-server/http/HttpResponse.h>

void HttpResponse::print() const
{
    print(std::cout);
}

void HttpResponse::print(std::ostream & ss) const
{
    printResponseLine(ss);
    printHeader(ss);
    printBody(ss);
}

void HttpResponse::printResponseLine(std::ostream &os) const
{
    os << http_version << " " << static_cast<int>(status_code) << " " << ReasonPhrase(status_code) << "\r\n";
}