//
// Created by Julia on 2019-12-20.
//

#include <http-server/Building/Room.h>

Room::Room(int idx, std::string name) : BuildingComponent(idx, name)
{

}

void Room::addEquipment(std::shared_ptr<Equipment> eq)
{
    equipment.insert({eq->getId(), eq});
}

std::shared_ptr<Equipment> Room::getEquipment(int idx)
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

void Room::deleteEquipment(int idx)
{
    equipment.erase(idx);
}

void Room::addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId)
{
    addEquipment(eq);
}

void Room::deleteEquipment(int eqId, int roomId, int floorId)
{
    deleteEquipment(eqId);
}

std::shared_ptr<Equipment> Room::getEquipment(int idx, int roomId, int floorId)
{
    return getEquipment(idx);
}

void Room::showMyInfo( json &j)
{
    BuildingComponent::convertToJson(j);
   j["@class-name"]="Room";
    j["idx"]=idx;
    j["name"]=name;
}

void  Room::showMyEq( json &j)
{
for (auto eq : equipment)
    j.push_back(eq.second);
}

std::shared_ptr<BuildingComponent> Room::getChild(int id)
{
    return nullptr;
}

void Room::convertToJson(json &j)
{
    BuildingComponent::convertToJson(j);
    j["@class-name"] = "Room";
    j["equipment"] = equipment;
}

void Room::convertFromJson(const json &j)
{
    BuildingComponent::convertFromJson(j);
    auto equipment_json = j.at("equipment");
    if(equipment_json.empty() == false)
        j.at("equipment").get_to(equipment);
}
