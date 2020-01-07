//
// Created by Julia on 2019-12-20.
//

#include <http-server/BuildingSystem/CompositePattern/Room.h>

#include "http-server/BuildingSystem/CompositePattern/Room.h"

namespace BuildingSystem
{
    Room::Room(int idx, std::string name) : Component(idx, 0, name)
    {

    }

    void Room::add_equipment(std::shared_ptr<Equipment> equipment)
    {
        equipment_map.insert({equipment->get_id(), equipment});
    }

    std::shared_ptr<Equipment> Room::get_equipment(int idx)
    {
        try
        {
            return equipment_map.at(idx);
        }
        catch (...)
        {
            return nullptr;
        }
    }

    void Room::delete_equipment(int idx)
    {
        equipment_map.erase(idx);
    }

    void Room::create_structure_json(json &j)
    {
        auto read_lock = Component::get_read_lock();
        j["idx"]=idx;
        j["name"]=name;
    }

    void  Room::create_equipment_json(json &j)
    {
        auto read_lock = Component::get_read_lock();
        for (auto eq : equipment_map)
            j.push_back(eq.second);
    }

    void Room::to_json(json &j)
    {
        auto read_lock = Component::get_read_lock();
        Component::to_json(j);
        j["@class-name"] = "Room";
        j["equipment"] = equipment_map;
    }

    void Room::from_json(const json &j)
    {
        Component::from_json(j);
        auto equipment_json = j.at("equipment");
        if(equipment_json.empty() == false)
            j.at("equipment").get_to(equipment_map);
    }

    bool Room::is_balanced()
    {
        return true;
    }
}
