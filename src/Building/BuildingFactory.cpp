//
// Created by Julia on 2019-12-20.
//

#include "../../include/http-server/Building/BuildingFactory.h"

BuildingFactory::BuildingFactory()
{
    reset();
}

void BuildingFactory::reset()
{
    floor_idx = 0;
    room_idx = 0;
    constructedComponent.reset(new BuildingComposite(idx, ""));
}

void BuildingFactory::addFloor(const std::string &name)
{
    floor_idx++;
    constructedComponent->add_child(std::make_shared<BuildingComposite>(floor_idx, name));
    room_idx = 0;
}

void BuildingFactory::addRoom(const std::string &name)
{
    room_idx++;
    constructedComponent->buildingComponents.back()->add_child(std::make_shared<Room>(room_idx, name));
}

void BuildingFactory::addEquipment(std::shared_ptr<Equipment> equipment)
{
    std::dynamic_pointer_cast<BuildingComposite>(
            constructedComponent->buildingComponents.back()
    )->buildingComponents.back()->add_equipment(std::move(equipment));
}

std::shared_ptr<BuildingComposite> BuildingFactory::getResult(const std::string &name)
{
    idx++;
    auto result = constructedComponent;
    result->idx = idx;
    result->name = name;
    reset();
    return result; //Make a copy of constructedComponent
}

std::shared_ptr<BuildingComponent> BuildingFactory::getExample()
{
    BuildingFactory factory;

    for (int i=1; i<3;i++){
        factory.addFloor("Floor");
        for (int j=1; j<4;j++){
            factory.addRoom("Room");
            std::shared_ptr<Equipment> eq = std::make_shared<Equipment>("lozeczko", Equipment::Type::OTHER);
            factory.addEquipment(eq);
        }
    }
    return factory.getResult("Ul. Ulicowa 1");
}
