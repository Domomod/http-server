//
// Created by dominik on 05.11.19.
//

#include <http-server/tcp-server.h>
#include <http-server/Building/BuildingSystem.h>
#include <http-server/Building/HttpAdapter.h>
#include <iostream>


int main(int argc, char *argv[])
{
    BuildingSystem buildingSystem;
    Threaded_tcp_server threaded_tcp_server(1235, buildingSystem.getHttpAdapter());
    threaded_tcp_server.loop();
}