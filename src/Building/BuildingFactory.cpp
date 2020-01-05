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

void BuildingFactory::add_floor(const std::string &name)
{
    floor_idx++;
    constructedComponent->add_child(std::make_shared<BuildingComposite>(floor_idx, name));
    room_idx = 0;
}

void BuildingFactory::add_room(const std::string &name)
{
    room_idx++;
    constructedComponent->buildingComponents.back()->add_child(std::make_shared<Room>(room_idx, name));
}

void BuildingFactory::add_equipment(std::shared_ptr<Equipment> equipment)
{
    std::dynamic_pointer_cast<BuildingComposite>(
            constructedComponent->buildingComponents.back()
    )->buildingComponents.back()->add_equipment(std::move(equipment));
}

std::shared_ptr<BuildingComposite> BuildingFactory::get_result(const std::string &name)
{
    idx++;
    auto result = constructedComponent;
    result->idx = idx;
    result->name = name;
    reset();
    return result; //Make a copy of constructedComponent
}

std::shared_ptr<BuildingComponent> BuildingFactory::get_example()
{
    BuildingFactory factory;

    for (int i=1; i<3;i++){
        factory.add_floor("Floor");
        for (int j=1; j<4;j++){
            factory.add_room("Room");
            std::shared_ptr<Equipment> eq = std::make_shared<Equipment>("lozeczko", Equipment::Type::OTHER);
            factory.add_equipment(eq);
        }
    }
    return factory.get_result("Ul. Ulicowa 1");
}
