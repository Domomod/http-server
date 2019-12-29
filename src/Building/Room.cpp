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

void Room::deleteEquipment(int eqId, int roomId, int floorId) {
    deleteEquipment(eqId);
}

std::shared_ptr<Equipment> Room::getEquipment(int idx,int roomId, int floorId ) {
    return getEquipment(idx);
}

std::string Room::showMyInfo(){
    std::string message="Room number: "+std::to_string(idx)+", "+name+"\n";
    message+"Number of items inside: "+std::to_string(equipment.size())+"\n";
    return message;
}
std::string Room::showMyEq(){
    std::string message="Room number: "+std::to_string(idx)+" inventory list\n";
    std::map<int, std::shared_ptr<Equipment>>::iterator iter;
    for (iter=equipment.begin(); iter!=equipment.end();iter++){
        message+=iter->second->showInfo();
    }
    return message;
}

std::shared_ptr<BuildingComponent> Room::getChild(int id)
{
    return nullptr;
}
