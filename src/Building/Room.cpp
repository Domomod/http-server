//
// Created by Julia on 2019-12-20.
//

#include "../../include/http-server/Building/Room.h"
Room::Room(int idx, std::string name) :BuildingComponent(idx, name){

}
void Room::addEquipment(std::shared_ptr<Equipment> eq){
    equipment.push_back(eq);
}
std::shared_ptr<Equipment> Room::getEquipment(int idx){
    for (auto eq : equipment){
        if (eq->getId()==idx)
            return eq;
    }
    return nullptr;
}
void Room::deleteEquipment(int idx){
    for (int i=0; i<equipment.size();i++){
        if (equipment[i]->getId()==idx)
                equipment.erase(equipment.begin()+i); //Not sure if it will work properly
    }
}