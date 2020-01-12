//
// Created by dominik on 05.11.19.
//

#include <HttpServer/tcp-server.h>
#include <BuildingSystem/ThreadsafeFacade.h>
#include <BuildingSystem/HttpAdapter.h>
#include <iostream>


int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        std::stringstream ss(argv[1]);
        uint16_t port;
        ss >> port;
        BuildingSystem::ThreadsafeFacade buildingSystem;
        HttpServer::Threaded_tcp_server threaded_tcp_server(port, buildingSystem.get_http_adapter());
        threaded_tcp_server.loop();
    }
}