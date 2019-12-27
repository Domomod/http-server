//
// Created by Julia on 2019-12-20.
//

#include <http-server/Building/Room.h>

#include "../../include/http-server/Building/Room.h"
Room::Room(int idx, std::string name) :BuildingComponent(idx, name){

}
void Room::addEquipment(std::shared_ptr<Equipment> eq){
    equipment.insert({eq->getId(),eq});
}
std::shared_ptr<Equipment> Room::getEquipment(int idx){
    try {
        return equipment.at(idx);
    }
    catch (...){
        return nullptr;}
}
void Room::deleteEquipment(int idx){
    equipment.erase(idx);
}

void Room::addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId) {
addEquipment(eq);}
