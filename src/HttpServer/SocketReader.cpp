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

            if(n <= 0)
            {
                this->end_connection = true;
            }

            buf[n] = 0;
            unprocessed_data += buf;

            /*HttpParser will remove already parsed data from buffer*/
            httpParser.parse_and_update_buffer(unprocessed_data);

            if(httpParser.is_request_ready())
            {
                return httpParser.get_request();
            }
        }
    }

    SocketReader::~SocketReader()
    {
        close(connection_socket_descriptor);
    }

    bool SocketReader::is_connection_ended() const
    {
        return !end_connection;
    }

#pragma clang diagnostic pop


}