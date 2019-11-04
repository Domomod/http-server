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
#include "http/HttpRequest.h"

#define SERVER_PORT 1235
#define QUEUE_SIZE 3

std::string executable_name;

class Threaded_tcp_server
{
public:
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

    void init_server_adress()
    {
        memset(&server_address, 0, sizeof(struct sockaddr));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(SERVER_PORT);
    }

    void init_socket_descriptor_with_error_check(char &reuse_addr_val)
    {
        server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket_descriptor < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie utworzenia gniazda..\n";
            //    exit(1);
        }
        setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse_addr_val,
                   sizeof(reuse_addr_val));
    }

    void bind_with_error_check() const
    {
        int bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
        if (bind_result < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n";
            exit(1);
        }
    }

    void listen_with_error_check() const
    {
        int listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
        if (listen_result < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie ustawienia wielkości kolejki.\n";
            exit(1);
        }
    }

    void handleConnection()
    {
        int connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if (connection_socket_descriptor < 0)
        {
            std::cerr << executable_name << ": Błąd przy próbie utworzenia gniazda dla połączenia.\n";
            exit(1);
        }

        pthread_mutex_lock(&mutex);
        for (int i = 0; i < QUEUE_SIZE; i++)
        {
            if (connection_socket_descriptors[i] == 0)
            {
                connection_socket_descriptors[i] = connection_socket_descriptor;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        std::thread th(ThreadBehavior, connection_socket_descriptor, connection_socket_descriptors);
        th.detach();

    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    static void *ThreadBehavior(int connection_socket_descriptor, int *all_connection_socket_descriptors)
    {
        std::__cxx11::string message;
        char buf[101];
        std::__cxx11::string end_of_request = "\r\n\r\n";


        ssize_t n;
        while (true)
        {
            n = read(connection_socket_descriptor, buf, sizeof(buf)-1);
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
    int connection_socket_descriptors[3] = {0, 0, 0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};


int main(int argc, char *argv[])
{
    executable_name = argv[0];
    Threaded_tcp_server threaded_tcp_server(1235);
    threaded_tcp_server.loop();
}