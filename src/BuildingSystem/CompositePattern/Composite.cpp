//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include <BuildingSystem/CompositePattern/Composite.h>
#include <BuildingSystem/CompositePattern/Composite.h>


namespace BuildingSystem
{
    Composite::Composite(int idx, std::string name) : Component(idx, name)
    {
    }

    void Composite::add_child(std::shared_ptr<Component> child)
    {
        if(buildingComponents.find(child->get_idx()) != buildingComponents.end()) throw ResourceAlreadyExists();

        buildingComponents.emplace(child->get_idx(),child);
    }

    std::shared_ptr<Component> Composite::get_child(int id)
    {
        auto record = buildingComponents.find(id);
        if( record == buildingComponents.end()) throw ResourceNotFound();
        return record->second;
    }

    void Composite::delete_child(int id)
    {
        if( buildingComponents.find(id) == buildingComponents.end()) throw ResourceNotFound();
        buildingComponents.erase(id);
    }

    void Composite::create_structure_json(json &j)
    {
        auto read_lock = Component::get_read_lock();
        Component::to_json(j);
        j["idx"]=idx;
        j["name"]=name;
        for (auto& [key, build]: buildingComponents)
        {
            json j2;
            build->create_structure_json(j2);
            j["structure"].push_back(j2);
        }
    }

    void Composite::create_equipment_json(json &j)
    {
        auto read_lock = Component::get_read_lock();
        for (auto& [key, build]: buildingComponents)
            build->create_equipment_json(j);
    }

    void Composite::to_json(json &j)
    {
        auto read_lock = Component::get_read_lock();
        Component::to_json(j);
        j["@class-name"] = typeid(Composite).name();
        j["buildingComponents"] = buildingComponents;
    }

    void Composite::from_json(const json &j)
    {
        Component::from_json(j);
        j.at("buildingComponents").get_to(buildingComponents);

        auto & front_child = buildingComponents.begin()->second;
    }
}