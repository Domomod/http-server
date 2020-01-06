//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include "http-server/BuildingSystem/CompositePattern/Composite.h"


namespace BuildingSystem
{
    Composite::Composite(int idx, std::string name) : Component(idx, name)
    {
    }

    void Composite::add_child(std::shared_ptr<Component> buildingComponent)
    {
        buildingComponents.push_back(buildingComponent);
    }

    std::shared_ptr<Component> Composite::get_child(int id)
    {
        for (std::shared_ptr<Component> component : buildingComponents)
        {
            if (component->get_idx() == id)
            {
                return component;
            }
        }
        throw ResourceNotFound();
    }

    void Composite::delete_child(int floorId)
    {
        for (int i = 0; i < buildingComponents.size(); i++)
        {
            if (buildingComponents[i]->get_idx() == floorId)
            {
                buildingComponents.erase(buildingComponents.begin() + i);
                return;
            }
        }
        throw ResourceNotFound();
    }

    void Composite::create_structure_json(json &j)
    {
        Component::to_json(j);
        j["idx"]=idx;
        j["name"]=name;
        for (auto build: buildingComponents)
        {
            json j2;
            build->create_structure_json(j2);
            j["structure"].push_back(j2);
        }
    }

    void Composite::create_equipment_json(json &j)
    {
        for (auto build: buildingComponents)
            build->create_equipment_json(j);
    }

    void Composite::to_json(json &j)
    {
        Component::to_json(j);
        j["@class-name"] = "BuildingComposite";
        j["buildingComponents"] = buildingComponents;
    }

    void Composite::from_json(const json &j)
    {
        Component::from_json(j);
        j.at("buildingComponents").get_to(buildingComponents);
    }
}