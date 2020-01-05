//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include <http-server/Building/BuildingComposite.h>

BuildingComposite::BuildingComposite(int idx, std::string name) : BuildingComponent(idx, name)
{
}

void BuildingComposite::add_child(std::shared_ptr<BuildingComponent> buildingComponent)
{
    buildingComponents.push_back(buildingComponent);
}

std::shared_ptr<BuildingComponent> BuildingComposite::get_child(int id)
{
    for (std::shared_ptr<BuildingComponent> component : buildingComponents)
    {
        if (component->get_idx() == id)
        {
            return component;
        }
    }
    return nullptr;
}

void BuildingComposite::delete_child(int floorId)
{
    for (int i = 0; i < buildingComponents.size(); i++)
    {
        if (buildingComponents[i]->get_idx() == floorId)
        {
            buildingComponents.erase(buildingComponents.begin() + i);
            return;
        }
    }
}

void BuildingComposite::create_structure_json(json &j)
{
    BuildingComponent::to_json(j);
    j["idx"]=idx;
    j["name"]=name;
    for (auto build: buildingComponents)
    {
        json j2;
        build->create_structure_json(j2);
        j["structure"].push_back(j2);
    }
}

void BuildingComposite::create_equipment_json(json &j)
{
    for (auto build: buildingComponents)
        build->create_equipment_json(j);
}

void BuildingComposite::to_json(json &j)
{
    BuildingComponent::to_json(j);
    j["@class-name"] = "BuildingComposite";
    j["buildingComponents"] = buildingComponents;
}

void BuildingComposite::from_json(const json &j)
{
    BuildingComponent::from_json(j);
    j.at("buildingComponents").get_to(buildingComponents);
}
