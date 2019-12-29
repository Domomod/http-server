//
// Created by dominik on 29.12.19.
//

#ifndef HTTP_SERVER_BUILDINGVISITOR_H
#define HTTP_SERVER_BUILDINGVISITOR_H

#include <memory>
#include <list>
#include <http-server/http/exceptions/HttpException.h>
#include "BuildingComponent.h"
class BuildingVisitor
{
public:
    std::shared_ptr<BuildingComponent> follow_path(std::shared_ptr<BuildingComponent>& start, std::list<int> path)
    {
        auto node = start;
        while(!path.empty()){
            int child_id = path.front();
            node = node->getChild(child_id);
            if(node == nullptr) throw HttpException(StatusCode::Gone ,"Resource is gone.");
            path.pop_front();
        }
        return node;
    }

};


#endif //HTTP_SERVER_BUILDINGVISITOR_H
