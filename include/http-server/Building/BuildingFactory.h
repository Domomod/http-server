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
    BuildingFactory(std::string name)
    {
        reset(name);
    }

    void reset(std::string name)
    {
        floor_idx = 0;
        room_idx = 0;
        constructedComponent.reset(new BuildingComposite(idx, std::move(name)));
    }

    void addFloor(const std::string &name = "")
    {
        floor_idx++;
        constructedComponent->addChild(std::make_shared<BuildingComposite>(floor_idx, name));
        room_idx = 0;
    }

    void addRoom(const std::string &name = "")
    {
        room_idx++;
        constructedComponent->buildingComponents.back()->addChild(std::make_shared<Room>(room_idx, name));
    }

    void addEquipment(std::shared_ptr<Equipment> equipment)
    {
        std::dynamic_pointer_cast<BuildingComposite>(
                constructedComponent->buildingComponents.back()
                )->buildingComponents.back()->addEquipment(std::move(equipment));
    }

    std::shared_ptr<BuildingComposite> getResult()
    {
        constructedComponent->idx = idx;
        idx++;
        return std::make_shared<BuildingComposite>(*constructedComponent); //Make a copy of constructedComponent
    }

    static std::shared_ptr<BuildingComponent> getExample(){
        BuildingFactory factory("Ul. Ulicowa 1");

        for (int i=1; i<2;i++){
            factory.addFloor("Floor");
            for (int j=1; j<3;j++){
                factory.addRoom("Room");
                std::shared_ptr<Equipment> eq = std::make_shared<Equipment>("lozeczko", Equipment::Type::OTHER);
                factory.addEquipment(eq);
            }
        }
        return factory.getResult();
    }
};


#endif //HTTP_SERVER_BUILDINGFACTORY_H
