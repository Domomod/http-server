//
// Created by dominik on 05.11.19.
//

#include <http-server/tcp-server.h>
#include <http-server/Building/BuildingSystem.h>
#include <http-server/Building/BuildingFactory.h>
int main(int argc, char *argv[])
{
    BuildingSystem bs;
    bs.add({}, BuildingFactory::getExample());
    bs.move(1,{1,1,1},{1,2,3});
    Threaded_tcp_server threaded_tcp_server(1234);
    threaded_tcp_server.loop();
}