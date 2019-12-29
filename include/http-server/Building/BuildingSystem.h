//
// Created by dominik on 29.12.19.
//

#ifndef HTTP_SERVER_BUILDINGVISITOR_H
#define HTTP_SERVER_BUILDINGVISITOR_H

#include <memory>
#include <list>
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

    std::shared_ptr<BuildingComponent> find(std::list<int> path)
    {
        auto node = root;
        while (!path.empty())
        {
            int child_id = path.front();
            node = node->getChild(child_id);
            if (node == nullptr) throw HttpException(StatusCode::Gone, "Resource is gone.");
            path.pop_front();
        }
        return node;
    }

    void add(std::list<int> path, std::shared_ptr<BuildingComponent> child)
    {
        auto node = find(path);
        node->addChild(child);
    }

    void remove(std::list<int> path)
    {
        if (!path.empty())
        {
            int removed_id = path.back();
            path.pop_back();
            auto node = find(path);
            node->deleteChild(removed_id);
        }
        else
        {
            root.reset(new BuildingComposite(0, "System root"));
        }
    }

    void move(int eq_id, std::list<int> source_path, std::list<int> dest_path)
    {
        auto source = find(source_path);
        auto destination = find(dest_path);
        auto equipment = source->getEquipment(eq_id);
        destination->addEquipment(equipment);
        source->deleteEquipment(eq_id);
    }
};


#endif //HTTP_SERVER_BUILDINGVISITOR_H
