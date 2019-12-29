//
// Created by dominik on 05.11.19.
//

#include <http-server/tcp-server.h>
#include <http-server/http/HttpRequestReader.h>
#include <http-server/bsd/BsdSocket_HttpRequestReader.h>
#include <http-server/http/HttpResponse.h>
#include <http-server/http/HttpResponseBuilder.h>
#include <boost/xpressive/xpressive.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

Threaded_tcp_server::Threaded_tcp_server(uint16_t server_port, int queue_size) : server_port(server_port),
                                                                                 queue_size(queue_size)
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
void *Threaded_tcp_server::ThreadBehavior(int connection_socket_descriptor)
{
    HttpRequestReader *httpRequestReader = new BsdSocket_HttpRequestReader(connection_socket_descriptor);
    HttpResponseBuilder httpResponseBuilder;

    while (true)
    {
        HttpRequest request = httpRequestReader->getRequest();
        request.print();
        using namespace boost::xpressive;

        sregex get_regex = sregex::compile(
                "^GET /buildings"
                "("
                /**/"/(?P<building>[[:digit:]]+)"
                /**/"("
                /*  */"/floors/(?P<floor>[[:digit:]]+)"
                /*  */"(/rooms/(?P<room>[[:digit:]]+))?"
                /**/")?"
                ")?"
                "/(?P<what>equipment|structure)"
        );

        sregex put_regex = sregex::compile(
                "^PUT /buildings"
                "("
                /**/"/(?P<building>[[:digit:]]+)/floors"
                /**/"("
                /*  */"/(?P<floor>[[:digit:]]+)/rooms"
                /*      */"("
                /*      */"/(?P<room>[[:digit:]]+)/equipment"
                /*  */")?"
                /**/")?"
                ")?$"
        );

        sregex post_regex = sregex::compile(
                "^POST /buildings(?P<building>[[:digit:]]+)"
                "/floors/(?P<floor>[[:digit:]]+)"
                "/rooms/(?P<room>[[:digit:]]+)"
                "/equipment/(?P<equipment>[[:digit:]]+)"
                "$"
        );

        sregex destination_regex = sregex::compile(
                "^/buildings(?P<building>[[:digit:]]+)"
                "/floors/(?P<floor>[[:digit:]]+)"
                "/rooms/(?P<room>[[:digit:]]+)"
                "$"
        );

        sregex delete_regex = sregex::compile(
                "^DELETE /buildings/(?P<building>[[:digit:]]+)"
                "("
                /**/"/floors/(?P<floor>[[:digit:]]+)"
                /**/"("
                /*  */"/rooms/(?P<room>[[:digit:]]+)"
                /*  */"("
                /*      */"/equipment/(?P<equipment>[[:digit:]]+)"
                /*  */")?"
                /**/")?"
                ")?$"
        );

        std::string str = request.getRequest();
        smatch match_path;
        if (regex_search(str, match_path, get_regex))
        {
            int building = std::atoi(match_path["building"].str().c_str());
            int floor = std::atoi(match_path["floor"].str().c_str());
            int room = std::atoi(match_path["room"].str().c_str());
            std::string what = match_path["what"].str();
            /*ZAWSZE PODANE JEST WHAT*/
        }
        else if (regex_search(str, match_path, post_regex))
        {
            auto values = request.getFieldValue("destination");
            if (values.size() == 1 && values[0] != HttpRequest::NO_SUCH_KEY)
            {
                smatch match_destination;
                if (regex_search(str, match_destination, destination_regex))
                {
                    int source_building = std::atoi(match_path["building"].str().c_str());
                    int source_floor = std::atoi(match_path["floor"].str().c_str());
                    int source_room = std::atoi(match_path["room"].str().c_str());
                    int source_equipment = std::atoi(match_path["equipment"].str().c_str());

                    int destination_building = std::atoi(match_destination["building"].str().c_str());
                    int destination_floor = std::atoi(match_destination["floor"].str().c_str());
                    int destination_room = std::atoi(match_destination["room"].str().c_str());

                    /*W OBU PRZYPADKACH ZAWSZE WSZYSTKO PODANE*/
                }
                else
                {
                    /*DESTINATION IS GARBAGE*/
                }
            }
            else
            {
                /*DESTINATION NOT GIVEN*/
            }
        }
        else if (regex_search(str, match_path, delete_regex))
        {
            int source_building = std::atoi(match_path["building"].str().c_str());
            int source_floor = std::atoi(match_path["floor"].str().c_str());
            int source_room = std::atoi(match_path["room"].str().c_str());
            int source_equipment = std::atoi(match_path["equipment"].str().c_str());
            /*CO NAJMNIEJ BUILDING PODANE*/
        }
        else if (regex_search(str, match_path, put_regex))
        {
            int source_building = std::atoi(match_path["building"].str().c_str());
            int source_floor = std::atoi(match_path["floor"].str().c_str());
            int source_room = std::atoi(match_path["room"].str().c_str());
            int source_equipment = std::atoi(match_path["equipment"].str().c_str());
            /*JEŚLI NIC NIE PODANE DODAJEMY BUDYNEK
             *JEŚLI PODANY JEST BUDYNEK TO DODAJEMY PIĘTRO
             *JEŚLI PODANY JEST BUDYNEK I PIĘTRO DODAJEMY POKÓJ*/
        }

        HttpResponse httpResponse = httpResponseBuilder
                .setStatusCode(StatusCode::OK)
                .setHeaderInfo({
                                       {"Server",       {"Test"}},
                                       {"Connection",   {"close"}},
                                       {"Content-Type", {"text/xml"}}
                               })
                .setBody("<xml=1.1>\n"
                         "<init>\n"
                         "\t<dana>Siema</dana>\n"
                         "</init>")
                .getResponse();

        std::string strResponse = httpResponse.toSendableString();
        std::cout << "\n\n" << strResponse << "\n\n";
        write(connection_socket_descriptor, strResponse.c_str(), strResponse.size());
    }

    delete httpRequestReader;
}
#pragma clang diagnostic pop

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