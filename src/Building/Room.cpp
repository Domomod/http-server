//
// Created by Julia on 2019-12-20.
//

#include <http-server/Building/Room.h>

Room::Room(int idx, std::string name) : BuildingComponent(idx, name)
{

}

void Room::add_equipment(std::shared_ptr<Equipment> eq)
{
    equipment.insert({eq->getId(), eq});
}

std::shared_ptr<Equipment> Room::get_equipment(int idx)
{
    try
    {
        return equipment.at(idx);
    }
    catch (...)
    {
        return nullptr;
    }
}

void Room::delete_equipment(int idx)
{
    equipment.erase(idx);
}

void Room::addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId)
{
    add_equipment(eq);
}

void Room::deleteEquipment(int eqId, int roomId, int floorId)
{
    delete_equipment(eqId);
}

std::shared_ptr<Equipment> Room::getEquipment(int idx, int roomId, int floorId)
{
    return get_equipment(idx);
}

void Room::create_structure_json(json &j)
{
    j["idx"]=idx;
    j["name"]=name;
}

void  Room::create_equipment_json(json &j)
{
for (auto eq : equipment)
    j.push_back(eq.second);
}

std::shared_ptr<BuildingComponent> Room::get_child(int id)
{
    return nullptr;
}

void Room::to_json(json &j)
{
    BuildingComponent::to_json(j);
    j["@class-name"] = "Room";
    j["equipment"] = equipment;
}

void Room::from_json(const json &j)
{
    BuildingComponent::from_json(j);
    auto equipment_json = j.at("equipment");
    if(equipment_json.empty() == false)
        j.at("equipment").get_to(equipment);
}
