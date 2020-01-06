//
// Created by Julia on 2019-12-20.
//

#include "http-server/Building/CompositePattern/ComponentFactory.h"

namespace BuildingSystem
{
    ComponentFactory::ComponentFactory()
    {
        reset();
    }

    void ComponentFactory::reset()
    {
        floor_idx = 0;
        room_idx = 0;
        constructedComponent.reset(new Composite(idx, ""));
    }

    void ComponentFactory::add_floor(const std::string &name)
    {
        floor_idx++;
        constructedComponent->add_child(std::make_shared<Composite>(floor_idx, name));
        room_idx = 0;
    }

    void ComponentFactory::add_room(const std::string &name)
    {
        room_idx++;
        constructedComponent->buildingComponents.back()->add_child(std::make_shared<Room>(room_idx, name));
    }

    void ComponentFactory::add_equipment(std::shared_ptr<Equipment> equipment)
    {
        std::dynamic_pointer_cast<Composite>(
                constructedComponent->buildingComponents.back()
        )->buildingComponents.back()->add_equipment(std::move(equipment));
    }

    std::shared_ptr<Composite> ComponentFactory::get_result(const std::string &name)
    {
        idx++;
        auto result = constructedComponent;
        result->idx = idx;
        result->name = name;
        reset();
        return result; //Make a copy of constructedComponent
    }

    std::shared_ptr<Component> ComponentFactory::get_example()
    {
        ComponentFactory factory;

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
}
