//
// Created by dominik on 04.11.19.
//

#include <http-server/http/HttpRequest.h>
#include <http-server/http/HttpParser.h>


void HttpParser::parse_line(const std::__cxx11::string &line)
{
    if (!isInState(State::HTTP_REQUEST_READY))
    {
        if (isInState(State::PARSING_HTTP_REQUEST_LINE))
        {
            parse_request_line(line);
        }
        else if (line.empty())
        {
            check_if_request_has_body();
        }
        else if (isInState(State::PARSING_HTTP_HEADER_FIELDS))
        {
            parse_header_field(line);
        }
        else if (isInState(State::PARSING_HTTP_MESSAGE_BODY))
        {
            parse_body_line(line);
        }
    }
    else
    {
        std::cerr << "HttpParser can't proceed to parse lines because it contains a httpRequest fully parsed\n "
                     "You need to either get or discard it";
        exit(-1);
    }

}

void HttpParser::parse_request_line(const std::string &line)
{
    std::vector<std::__cxx11::string> words;
    iter_split(words, line, boost::algorithm::first_finder(" "));
    httpRequest->request_type = words[0];
    httpRequest->path = words[1];
    httpRequest->http_version = words[2];
    currentState = State::PARSING_HTTP_HEADER_FIELDS;
}

void HttpParser::parse_header_field(const std::string &line)
{
    std::vector<std::__cxx11::string> words;
    iter_split(words, line, boost::algorithm::first_finder(" "));

    for (auto &word : words)
    {
        if (word.back() == ':' || word.back() == ',')
        {
            word.pop_back();
        }
    }

    httpRequest->header_info.insert(
            std::pair<std::__cxx11::string, std::vector<std::__cxx11::string>>(
                    words[0], std::vector<std::__cxx11::string>(words.begin() + 1, words.end())
            )
    );
}

void HttpParser::parse_body_line(const std::string &line)
{
    httpRequest->body.append(line);
    if(how_much_msg_body_left() == 0)
    {
        currentState = State::HTTP_REQUEST_READY;
    }
}


HttpParser::HttpParser()
{
    httpRequest = new HttpRequest();
    currentState = State::PARSING_HTTP_REQUEST_LINE;
}

void HttpParser::check_if_request_has_body()
{
    /*If a http request contains Content-Length header field, it also contains html body.
     *If for some reason Content-Length would be set to 0, this would also mean that body
     *is absent.
     * */
    std::vector<std::string> value_list = httpRequest->getFieldValue("Content-Length");
    if (value_list[0] == HttpRequest::NO_SUCH_KEY || value_list[0] == "0")
    {
        currentState = State::HTTP_REQUEST_READY;
    }
    else
    {
        currentState = State::PARSING_HTTP_MESSAGE_BODY;
    }
}

unsigned long HttpParser::how_much_msg_body_left()
{
    std::vector<std::string> value_list = httpRequest->getFieldValue("Content-Length");
    if (value_list[0] == HttpRequest::NO_SUCH_KEY)
    {
        return 0;
    }
    else
    {
        unsigned long content_length;
        std::stringstream sstream(value_list[0]);
        sstream >> content_length;
        return content_length - httpRequest->body.size();
    }
}

HttpRequest HttpParser::get_request()
{
    if (isInState(State::HTTP_REQUEST_READY))
    {
        HttpRequest request = *httpRequest;
        resetState();
        return request;
    }
    else
    {
        std::cerr << "HtppParser can't return a request before its fully parsed.";
        exit(-1);
    }
}

bool HttpParser::isInState(const HttpParser::State &state) const
{
    return currentState == state;
}

void HttpParser::discard()
{
    resetState();
}

void HttpParser::resetState()
{
    delete  httpRequest;
    httpRequest = new HttpRequest();
    currentState = State::PARSING_HTTP_REQUEST_LINE;
}

