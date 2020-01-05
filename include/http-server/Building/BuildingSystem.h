//
// Created by dominik on 29.12.19.
//

#ifndef HTTP_SERVER_BUILDINGVISITOR_H
#define HTTP_SERVER_BUILDINGVISITOR_H

#include <memory>
#include <list>
#include <queue>
#include <shared_mutex>
#include <http-server/http/exceptions/HttpException.h>
#include "BuildingComponent.h"
#include "BuildingComposite.h"
#include "Equipment.h"

class HttpAdapter;

class BuildingSystem
{
private:
    std::shared_ptr<BuildingComponent> root;
public:
    BuildingSystem();

    HttpAdapter getHttpAdapter();

    std::pair<std::shared_ptr<BuildingComponent>, std::queue<std::shared_lock<std::shared_mutex>>>
    find(std::list<int> path);

    std::string get_info(std::list<int> path);

    std::string get_equipment(std::list<int> path);

    void add(std::list<int> path, std::shared_ptr<BuildingComponent> child);

    void add(std::list<int> path, std::shared_ptr<Equipment> eq);

    void remove(std::list<int> path);

    void move(int eq_id, std::list<int> source_path, std::list<int> dest_path);
};


#endif //HTTP_SERVER_BUILDINGVISITOR_H
