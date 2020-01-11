//
// Created by dominik on 04.11.19.
//

#include <HttpServer/Request.h>
#include <HttpServer/RequestParser.h>

namespace HttpServer
{
    RequestParser::RequestParser()
    {
        httpRequest = new Request();
        currentState = State::PARSING_HTTP_REQUEST_LINE;
    }


    void RequestParser::parse_and_update_buffer(std::string &buffer)
    {
        while (currentState != State::HTTP_REQUEST_READY)
        {
            if (currentState == State::PARSING_HTTP_REQUEST_LINE && contains(buffer, '\n'))
            {
                std::string line = move_line(buffer);
                parse_request_line(line);
                currentState = State::PARSING_HTTP_HEADER_FIELDS;
            }
            else if (currentState == State::PARSING_HTTP_HEADER_FIELDS && contains(buffer, '\n'))
            {
                while (currentState == State::PARSING_HTTP_HEADER_FIELDS && contains(buffer, '\n'))
                {
                    std::string line = move_line(buffer);
                    if (line.empty())
                    {
                        currentState = State::PARSING_HTTP_MESSAGE_BODY;
                    }
                    else
                    {
                        parse_header(line);
                    }
                }
            }
            else if (currentState == State::PARSING_HTTP_MESSAGE_BODY && how_much_body_left() == 0)
            {
                /*Message's body was either fully parsed already, or message did not contain a body in the beginning*/
                currentState = State::HTTP_REQUEST_READY;
            }
            else if (currentState == State::PARSING_HTTP_MESSAGE_BODY && !buffer.empty())
            {
                unsigned long body_left = how_much_body_left();
                unsigned long buffer_length = buffer.size();
                if (buffer_length > body_left)
                {
                    /*Buffer contain's parts of another request. Extract only what's needed */
                    std::__cxx11::string line = split_on(buffer, body_left);
                    append_to_body(line);
                }
                else
                {
                    append_to_body(buffer);
                    buffer.erase();
                }
            }
            else
            {
                /*Data left in buffer is insufficient to continue parsing. Return and wait for next call*/
                return;
            }
        }
    }

    void RequestParser::parse_request_line(const std::string &line)
    {
        std::vector<std::__cxx11::string> words;
        iter_split(words, line, boost::algorithm::first_finder(" "));
        httpRequest->request = words[0] + " " + words[1];
        httpRequest->http_version = words[2];
    }

    void RequestParser::parse_header(const std::string &line)
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

    void RequestParser::append_to_body(const std::string &line)
    {
        httpRequest->body.append(line);
    }

    unsigned long RequestParser::how_much_body_left()
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
        Request request = *httpRequest;
        reset_state();
        return request;
    }

    bool RequestParser::is_request_ready() const
    {
        return currentState == State::HTTP_REQUEST_READY;
    }

    void RequestParser::reset_state()
    {
        delete httpRequest;
        httpRequest = new Request();
        currentState = State::PARSING_HTTP_REQUEST_LINE;
    }

    bool RequestParser::contains(const std::__cxx11::string &line, char character)
    {
        return line.find('\n') != std::string::npos;
    }

    std::string RequestParser::move_line(std::string &str)
    {
        std::__cxx11::string line = split_on(str, str.find('\n'));
        line.pop_back();
        return line;
    }

    std::string RequestParser::split_on(std::__cxx11::string &str, unsigned long n)
    {
        std::__cxx11::string first_part = str.substr(0, n);
        str = str.substr(n + 1);
        return first_part;
    }


}