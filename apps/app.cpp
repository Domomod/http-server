//
// Created by dominik on 05.11.19.
//

#include <http-server/tcp-server.h>

int main(int argc, char *argv[])
{
    Threaded_tcp_server threaded_tcp_server(1236);
    threaded_tcp_server.loop();
}