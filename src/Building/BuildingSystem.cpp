//
// Created by dominik on 29.12.19.
//

#include <http-server/Building/BuildingSystem.h>
#include <http-server/Building/HttpAdapter.h>

HttpAdapter BuildingSystem::getHttpAdapter()
{
    return HttpAdapter(*this);
}
