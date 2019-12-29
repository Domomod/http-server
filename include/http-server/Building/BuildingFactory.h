#include <utility>

//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGFACTORY_H
#define HTTP_SERVER_BUILDINGFACTORY_H


#include <string>
#include "BuildingComposite.h"
#include "BuildingComponent.h"
#include "Room.h"
class BuildingFactory
{
private:
    std::shared_ptr<BuildingComposite> constructedComponent;
    int idx = 0;
    int floor_idx = 0;
    int room_idx = 0;
public:
    void Reset(std::string name)
    {
        floor_idx = 0;
        room_idx = 0;
        constructedComponent.reset(new BuildingComposite(idx, std::move(name)));
    }

    void AddFloor()
    {
        floor_idx++;
        constructedComponent->addChild(std::make_shared<BuildingComposite>(floor_idx, ""));
        room_idx = 0;
    }

    void AddRoom()
    {
        room_idx++;
        constructedComponent->buildingComponents.back()->addChild(std::make_shared<Room>(room_idx, ""));
    }

    std::shared_ptr<BuildingComposite> GetResult()
    {
        constructedComponent->idx = idx;
        idx++;
        return std::make_shared<BuildingComposite>(*constructedComponent); //Make a copy of constructedComponent
    }

/*    static std::shared_ptr<BuildingComposite> GetExamplaryBuilding()
    {
    }*/

    BuildingFactory(std::string name)
    {
        Reset(name);
    }
};


#endif //HTTP_SERVER_BUILDINGFACTORY_H
