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

class BuildingSystem
{
private:
    std::shared_ptr<BuildingComponent> root;
public:
    BuildingSystem()
    {
        root.reset(new BuildingComposite(0, "System root"));
    }

    std::pair<std::shared_ptr<BuildingComponent>, std::queue<std::shared_lock<std::shared_mutex>>>
    find(std::list<int> path)
    {
        auto node = root;
        std::queue<std::shared_lock<std::shared_mutex>> locked_mutexes;
        while (!path.empty())
        {
            locked_mutexes.push(node->getReadLock());
            int child_id = path.front();
            node = node->getChild(child_id);
            if (node == nullptr) throw HttpException(StatusCode::Gone, "Resource is gone.");
            path.pop_front();
        }
        return {node, std::move(locked_mutexes)};
    }

    void add(std::list<int> path, std::shared_ptr<BuildingComponent> child)
    {
        auto result = find(path);
        auto& node = result.first;
        auto& mutexes = result.second;
        auto node_lock = node->getWriteLock();
        node->addChild(child);
    }

    void remove(std::list<int> path)
    {
        if (!path.empty())
        {
            int removed_id = path.back();
            path.pop_back();
            auto result = find(path);
            auto& node = result.first;
            auto& mutexes = result.second;
            auto node_lock = node->getWriteLock();
            node->deleteChild(removed_id);
        }
        else
        {
            root.reset(new BuildingComposite(0, "System root"));
        }
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-goto"
    void move(int eq_id, std::list<int> source_path, std::list<int> dest_path)
    {
        std::pair<std::shared_ptr<BuildingComponent>, std::queue<std::shared_lock<std::shared_mutex>>> result;

        std::shared_ptr<BuildingComponent> source;
        std::queue<std::shared_lock<std::shared_mutex>> source_mutexes;
        std::unique_lock<std::shared_mutex> source_lock;

        std::shared_ptr<BuildingComponent> destination;
        std::queue<std::shared_lock<std::shared_mutex>> destination_mutexes;
        std::unique_lock<std::shared_mutex> destination_lock;

        bool swap_order = dest_path < source_path;
        if(swap_order) goto swap_first;
        swap_second:
        result = find(source_path);
        source = std::move(result.first);
        source_mutexes = std::move(result.second);
        source_lock = source->getWriteLock();
        if(swap_order) goto swap_end;

        swap_first:
        result = find(dest_path);
        destination = result.first;
        destination_mutexes = std::move(result.second);
        destination_lock = destination->getWriteLock();
        if(swap_order) goto swap_second;

        swap_end:
        auto equipment = source->getEquipment(eq_id);
        destination->addEquipment(equipment);
        source->deleteEquipment(eq_id);
    }
#pragma clang diagnostic pop
};


#endif //HTTP_SERVER_BUILDINGVISITOR_H
