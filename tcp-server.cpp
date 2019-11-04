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

#include "http/HttpParser.h"

#define QUEUE_SIZE 3

std::string executable_name;

/*!
 * @brief A tcp threaded server. Creates a thread for each client communciating with the server.
 * The protocol of communication (http, ftp, etc...) and taken actions depend on a function provided by the user
 * during the initialization.
 */
class Threaded_tcp_server
{
public:
    /*!
     * @brief Initializes a threaded tcp server.
     * @param port port to open the service at
     * @param queue_size maximum number of opened sessions.
     */
    Threaded_tcp_server(int port, int queue_size = 3) : server_port(server_port), queue_size(queue_size)
    {
        char reuse_addr_val = 1;

        init_server_adress();

        init_socket_descriptor_with_error_check(reuse_addr_val);

        bind_with_error_check();

        listen_with_error_check();
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    /*!
     * @brief Performs server's tasks in an endless loop.
     */
    void loop()
    {
        while (1)
        {
            handleConnection();
        }
    }

#pragma clang diagnostic pop

    virtual ~Threaded_tcp_server()
    {
        close(server_socket_descriptor);
    }

private:

    /*!
     * @brief Initializes the server adress. Uses member variable server_port as the service's port.
     */
    void init_server_adress()
    {
        memset(&server_address, 0, sizeof(struct sockaddr));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(server_port);
    }

    /*!
     * @brief Creates a server socket descriptor. Stops the program on failure.
     * @param reuse_addr_val If set on true, server will be able to reopen on the same port more frequently.
     */    void init_socket_descriptor_with_error_check(char &reuse_addr_val)
    {
        server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket_descriptor < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie utworzenia gniazda..\n";
            exit(1);
        }
        setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse_addr_val,
                   sizeof(reuse_addr_val));
    }

    /*!
     * @brief Assigns an adress (often refered to as a 'name') to a socket.
     */
    void bind_with_error_check() const
    {
        int bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
        if (bind_result < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n";
            exit(1);
        }
    }


    /*!
     * @brief marks the socket referred to by sockfd as a passive socket,
     * that is, as a socket that will be used to accept incoming connection.
     * Stops the program on failure.
     */
    void listen_with_error_check() const
    {
        int listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
        if (listen_result < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie ustawienia wielkości kolejki.\n";
            exit(1);
        }
    }

    /*!
     * @brief Accepts connections, creates sockets for them. Creates a new thread designated to communicate with the client,
     * detaches it and immediatelly returns control to the caller.
     */
    void handleConnection()
    {
        int connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if (connection_socket_descriptor < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie utworzenia gniazda dla połączenia.\n";
            exit(1);
        }

        std::thread th(ThreadBehavior, connection_socket_descriptor);
        th.detach();
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    /*!
     * @brief Handles communication with the client.
     * @param connection_socket_descriptor Client's socket descriptor.
     */
    static void *ThreadBehavior(int connection_socket_descriptor)
    {
        std::__cxx11::string message;
        char buf[101];
        std::__cxx11::string end_of_request = "\r\n\r\n";


        ssize_t n;
        while (true)
        {
            n = read(connection_socket_descriptor, buf, sizeof(buf) - 1);
            buf[n] = 0;

            message += buf;
            std::size_t found = message.find(end_of_request);
            if (found != std::string::npos)
            {
                std::vector<std::string> message_substrings;
                boost::iter_split(message_substrings, message, boost::first_finder(end_of_request));

                auto http_message = HttpParser::parse_message(message_substrings[0]);
                http_message.print();
                std::cout << "INCOMING REQUEST:\n" << message_substrings[0];
                message = message_substrings[1];
            }

        }
    }

#pragma clang diagnostic pop

    int server_socket_descriptor;
    struct sockaddr_in server_address;
    const int server_port;
    const int queue_size;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};


int main(int argc, char *argv[])
{
    executable_name = argv[0];
    Threaded_tcp_server threaded_tcp_server(1235);
    threaded_tcp_server.loop();
}