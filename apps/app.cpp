//
// Created by dominik on 05.11.19.
//

#include <http-server/tcp-server.h>
#include <http-server/BuildingSystem/ThreadsafeFacade.h>
#include <http-server/BuildingSystem/HttpAdapter.h>
#include <iostream>


int main(int argc, char *argv[])
{
    BuildingSystem::ThreadsafeFacade buildingSystem;
    Threaded_tcp_server threaded_tcp_server(1235, buildingSystem.get_http_adapter());
    threaded_tcp_server.loop();
}