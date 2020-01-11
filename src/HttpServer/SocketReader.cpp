//
// Created by dominik on 22.11.19.
//

#include <HttpServer/SocketReader.h>

namespace HttpServer
{
    SocketReader::SocketReader(int connection_socket_descriptor)
            : connection_socket_descriptor(
            connection_socket_descriptor)
    {
    }


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    Request SocketReader::get_request()
    {
        while (true)
        {
            ssize_t n;
            n = read(connection_socket_descriptor, buf, sizeof(buf) - 1);
            //TODO: -1 i 0
            buf[n] = 0;
            unprocessed_data += buf;

            while (contains(unprocessed_data, '\n') &&
                   (httpParser.isInState(RequestParser::State::PARSING_HTTP_REQUEST_LINE) ||
                    httpParser.isInState(RequestParser::State::PARSING_HTTP_HEADER_FIELDS)))
            {
                std::__cxx11::string line = extractLine(unprocessed_data);
                httpParser.parse_line(line);
            }

            while (httpParser.isInState(RequestParser::State::PARSING_HTTP_MESSAGE_BODY) && !unprocessed_data.empty())
            {
                unsigned long how_much_left = httpParser.how_much_msg_body_left();
                if (how_much_left >= unprocessed_data.size())
                {
                    httpParser.parse_line(unprocessed_data);
                    unprocessed_data = "";
                }
                else
                {
                    std::__cxx11::string line = splitOnNth(unprocessed_data, how_much_left);
                    httpParser.parse_line(line);
                }
            }

            if (httpParser.isInState(RequestParser::State::HTTP_REQUEST_READY))
            {
                return httpParser.get_request();
            }
        }
    }


    bool SocketReader::contains(const std::__cxx11::string &line, char character)
    {
        return line.find('\n') != std::string::npos;
    }

    std::string SocketReader::extractLine(std::string &str)
    {
        std::__cxx11::string line = splitOnNth(str, str.find('\n'));
        line.pop_back();
        return line;
    }

    std::__cxx11::string SocketReader::splitOnNth(std::__cxx11::string &str, unsigned long n)
    {
        std::__cxx11::string first_part = str.substr(0, n);
        str = str.substr(n + 1);
        return first_part;
    }

    SocketReader::~SocketReader()
    {
        close(connection_socket_descriptor);
    }

#pragma clang diagnostic pop


}