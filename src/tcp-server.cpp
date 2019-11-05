//
// Created by dominik on 05.11.19.
//

#include <http-server/tcp-server.h>


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
Threaded_tcp_server::Threaded_tcp_server(uint16_t server_port, int queue_size) : server_port(server_port), queue_size(queue_size)
{
    char reuse_addr_val = 1;

    init_server_adress();

    init_socket_descriptor_with_error_check(reuse_addr_val);

    bind_with_error_check();

    listen_with_error_check();
}

void Threaded_tcp_server::loop()
{
    while (true)
    {
        handleConnection();
    }
}

Threaded_tcp_server::~Threaded_tcp_server()
{
    close(server_socket_descriptor);
}

void Threaded_tcp_server::init_server_adress()
{
    memset(&server_address, 0, sizeof(struct sockaddr));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(server_port);
}

void Threaded_tcp_server::bind_with_error_check() const
{
    int bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
    if (bind_result < 0)
    {
        std::cerr << "Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n";
        exit(1);
    }
}

void Threaded_tcp_server::listen_with_error_check() const
{
    int listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
    if (listen_result < 0)
    {
        std::cerr << "Błąd przy próbie ustawienia wielkości kolejki.\n";
        exit(1);
    }
}

void Threaded_tcp_server::handleConnection()
{
    int connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
    if (connection_socket_descriptor < 0)
    {
        std::cerr << "Błąd przy próbie utworzenia gniazda dla połączenia.\n";
        exit(1);
    }

    std::thread th(ThreadBehavior, connection_socket_descriptor);
    th.detach();
}

void *Threaded_tcp_server::ThreadBehavior(int connection_socket_descriptor)
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

void Threaded_tcp_server::init_socket_descriptor_with_error_check(char &reuse_addr_val)
{
    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_descriptor < 0)
    {
        std::cerr << "Błąd przy próbie utworzenia gniazda..\n";
        exit(1);
    }
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse_addr_val,
               sizeof(reuse_addr_val));
}


#pragma clang diagnostic pop