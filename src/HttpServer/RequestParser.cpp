//
// Created by dominik on 04.11.19.
//

#include <HttpServer/Request.h>
#include <HttpServer/RequestParser.h>

namespace HttpServer
{
    void RequestParser::parse_line(const std::__cxx11::string &line)
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

    void RequestParser::parse_request_line(const std::string &line)
    {
        std::vector<std::__cxx11::string> words;
        iter_split(words, line, boost::algorithm::first_finder(" "));
        httpRequest->request = words[0] + " " + words[1];
        httpRequest->http_version = words[2];
        currentState = State::PARSING_HTTP_HEADER_FIELDS;
    }

    void RequestParser::parse_header_field(const std::string &line)
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

    void RequestParser::parse_body_line(const std::string &line)
    {
        httpRequest->body.append(line);
        if (how_much_msg_body_left() == 0)
        {
            currentState = State::HTTP_REQUEST_READY;
        }
    }


    RequestParser::RequestParser()
    {
        httpRequest = new Request();
        currentState = State::PARSING_HTTP_REQUEST_LINE;
    }

    void RequestParser::check_if_request_has_body()
    {
        /*If a http request contains Content-Length header field, it also contains html body.
         *If for some reason Content-Length would be set to 0, this would also mean that body
         *is absent.
         * */
        std::vector<std::string> value_list = httpRequest->get_field_value("Content-Length");
        if (value_list[0] == Request::NO_SUCH_KEY || value_list[0] == "0")
        {
            currentState = State::HTTP_REQUEST_READY;
        }
        else
        {
            currentState = State::PARSING_HTTP_MESSAGE_BODY;
        }
    }

    unsigned long RequestParser::how_much_msg_body_left()
    {
        std::vector<std::string> value_list = httpRequest->get_field_value("Content-Length");
        if (value_list[0] == Request::NO_SUCH_KEY)
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

    Request RequestParser::get_request()
    {
        if (isInState(State::HTTP_REQUEST_READY))
        {
            Request request = *httpRequest;
            resetState();
            return request;
        }
        else
        {
            std::cerr << "HtppParser can't return a request before its fully parsed.";
            exit(-1);
        }
    }

    bool RequestParser::isInState(const RequestParser::State &state) const
    {
        return currentState == state;
    }

    void RequestParser::discard()
    {
        resetState();
    }

    void RequestParser::resetState()
    {
        delete httpRequest;
        httpRequest = new Request();
        currentState = State::PARSING_HTTP_REQUEST_LINE;
    }

}


