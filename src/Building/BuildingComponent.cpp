//insert
// Created by Julia on 2019-12-20.
//

#include <http-server/Building/Room.h>
#include <iostream>

#include "../../include/http-server/Building/BuildingComposite.h"

BuildingComponent::BuildingComponent(int _idx, std::string _name)
{
    this->idx = _idx;
    this->name = _name;
}

int BuildingComponent::get_idx()
{
    return idx;
}

std::string BuildingComponent::get_structure_json(int i)
{
    json j;
    this->create_structure_json(j);
    return j.dump(i);
}

std::string BuildingComponent::get_equipment_json(int i)
{
    json j;
    this->create_equipment_json(j);
    return j.dump(i);
}

void BuildingComponent::to_json(json &j)
{
    j["idx"] = idx;
    j["name"] = name;
}

void BuildingComponent::from_json(const json &j)
{
    j.at("idx").get_to(idx);
    j.at("name").get_to(name);
}

std::shared_lock<std::shared_mutex> BuildingComponent::get_read_lock()
{
    return std::move(std::shared_lock<std::shared_mutex>(guard));
}

std::unique_lock<std::shared_mutex> BuildingComponent::get_write_lock()
{
    return std::move(std::unique_lock<std::shared_mutex>(guard));
}

void to_json(json &j, const std::shared_ptr<BuildingComponent> &x)
{
    x->to_json(j);
}

void from_json(const json &j, std::shared_ptr<BuildingComponent> &a)
{
    std::string type;
    try
    {
        j.at("@class-name").get_to(type);
        if (type == "BuildingComposite")
            a.reset(new BuildingComposite());
        if (type == "Room")
            a.reset(new Room());

        a->from_json(j);
    }
    catch (...)
    {
        a.reset();
        throw std::runtime_error("Incorrect Json: Not a " + type + ".");
    }
}
