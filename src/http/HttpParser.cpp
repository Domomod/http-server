//
// Created by dominik on 04.11.19.
//

#include <http-server/http/HttpRequest.h>
#include <http-server/http/HttpParser.h>


HttpRequest HttpParser::parse_message(const std::__cxx11::string &message)
{
    HttpRequest httpRequest;

    std::vector<std::__cxx11::string> request_lines;
    iter_split(request_lines, message, boost::algorithm::first_finder("\r\n"));
    bool is_header = true;
    for (auto line : request_lines)
    {
        if (is_header)
        {
            parse_request_type(httpRequest, line);
            is_header = false;
        }
        else
        {
            parse_keys_and_values(httpRequest, line);
        }
    }
    return httpRequest;
}


void HttpParser::parse_keys_and_values(HttpRequest &httpRequest, std::__cxx11::string &line)
{
    std::vector<std::__cxx11::string> words;
    iter_split(words, line, boost::algorithm::first_finder(" "));

    for(auto& word : words){
        if (word.back() == ':' || word.back() == ',')
        {
            word.pop_back();
        }
    }



    httpRequest.header_info.insert(
                    std::pair<std::__cxx11::string, std::vector<std::__cxx11::string>>(
                            words[0], std::vector<std::__cxx11::string>(words.begin() + 1, words.end())
                    )
            );
}


void HttpParser::parse_request_type(HttpRequest &httpRequest, std::__cxx11::string &line)
{
    std::vector<std::__cxx11::string> words;
    iter_split(words, line, boost::algorithm::first_finder(" "));
    httpRequest.request_type = words[0];
    httpRequest.path = words[1];
    httpRequest.http_version = words[2];
}