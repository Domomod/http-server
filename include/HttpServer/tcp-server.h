#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>

#include "RequestParser.h"

#define QUEUE_SIZE 50

namespace HttpServer
{
/*!
 * @brief A tcp threaded server. Creates a thread for each client communicating with the server.\n
 * The protocol of communication (http, ftp, etc...) and taken actions depend on a function provided by the user\n
 * during the initialization.
 */
    class Threaded_tcp_server
    {
    public:
        /*!
         * @brief Initializes a threaded tcp server.
         * @param server_port port to open the service at
         * @param queue_size maximum number of opened sessions.
         */
        Threaded_tcp_server(const uint16_t server_port, const std::function<void(int)> &threadBeheaviour,
                            const int queue_size = 3);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

        /*!
         * @brief Performs server's tasks in an endless loop.
         */
        void loop();

#pragma clang diagnostic pop

        virtual ~Threaded_tcp_server();

    private:

        /*!
         * @brief Initializes the server adress. Uses member variable server_port as the service's port.
         */
        void init_server_adress();

        /*!
         * @brief Creates a server socket descriptor. Stops the program on failure.
         * @param reuse_addr_val If set on true, server will be able to reopen on the same port more frequently.
         */
        void init_socket_descriptor_with_error_check();

        /*!
         * @brief Assigns an adress (often refered to as a 'name') to a socket.
         */
        void bind_with_error_check() const;

        /*!
         * @brief marks the socket referred to by sockfd as a passive socket,
         * that is, as a socket that will be used to accept incoming connection.
         * Stops the program on failure.
         */
        void listen_with_error_check() const;

        /*!
         * @brief Accepts connections, creates sockets for them. Creates a new thread designated to communicate with the client,
         * detaches it and immediatelly returns control to the caller.
         */
        void handleConnection();

        int server_socket_descriptor;
        struct sockaddr_in server_address;
        const uint16_t server_port;
        const int queue_size;
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
        std::function<void(int)> threadBeheaviour;
    };
}

