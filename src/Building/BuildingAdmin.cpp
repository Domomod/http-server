//
// Created by Julia on 2019-12-28.
//

#include "../../include/http-server/Building/BuildingAdmin.h"

void BuildingAdmin::addBuilding(std::shared_ptr<BuildingComponent> building){
    buildings.insert({building->getIdx(),building});
}
void BuildingAdmin::addFloor(std::shared_ptr<BuildingComponent> floor, int buildingId){
    try {
        auto buildingptr=buildings.at(buildingId);
        buildingptr->addFloor(floor);
    }
    catch (...){
        std::string message="This building doesn't exist\n";
        throw message;
    }
}
void BuildingAdmin::addRoom(std::shared_ptr<BuildingComponent> room, int buildingId, int floorId){
    try {
        auto buildingptr=buildings.at(buildingId);
        buildingptr->addRoom(floorId,room);
    }
    catch (...){
        std::string message="Building or floor doesn't exist\n";
        throw message;
    }
}
void BuildingAdmin::addEquipment(std::shared_ptr<Equipment> eq, int buildingId, int floorId, int roomId){
    try {
        auto buildingptr=buildings.at(buildingId);
        buildingptr->addEquipment(eq, floorId, roomId);
    }
    catch (...){
        std::string message="This building doesn't exist\n";
        throw message;
    }
}
void BuildingAdmin::moveEquipment(int eqId, int buildingIdFrom, int floorIdFrom, int roomIdFrom, int buildingIdTo, int floorIdTo, int roomIdTo){
    try {
        auto buildingptr=buildings.at(buildingIdFrom);
        auto eq = buildingptr->getEquipment(eqId,roomIdFrom,floorIdFrom);
        buildingptr=buildings.at(buildingIdTo);
        buildingptr->addEquipment(eq, floorIdTo, roomIdTo);
    }
    catch (...){
        std::string message="This building doesn't exist\n";
        throw message;
    }
}
void BuildingAdmin::deleteBuilding(int id){
buildings.erase(id);
}
void BuildingAdmin::deleteFloor(int buildingId, int floorId){
    try {
        auto buildingptr=buildings.at(buildingId);
        buildingptr->deleteFloor(floorId);
    }
    catch (...){
        std::string message="This building doesn't exist\n";
        throw message;
    }

}
void BuildingAdmin::deleteRoom(int buildingId, int floorId, int roomId){
    try {
        auto buildingptr=buildings.at(buildingId);
        buildingptr->deleteRoom(floorId,roomId);
    }
    catch (...){
        std::string message="This building doesn't exist\n";
        throw message;
    }

}
void BuildingAdmin::deleteEquipment(int buildingId, int floorId, int roomId, int eqId){
    try {
        auto buildingptr=buildings.at(buildingId);
        buildingptr->deleteEquipment(eqId,roomId,floorId);
    }
    catch (...){
        std::string message="This building doesn't exist\n";
        throw message;
    }
}
std::string BuildingAdmin::allBuildingsInfo(){

}
std::string BuildingAdmin::buildingInfo_eq(int id){

}
std::string BuildingAdmin::buildingInfo_floor(int id){

}
std::string BuildingAdmin::floorInfo_rooms(int buildingId, int floorId ){

}
std::string BuildingAdmin::floorInfo_eq(int buildingId, int floorId){

}
std::string BuildingAdmin::roomInfo(int buildingId, int floorId, int roomId){

}
std::string BuildingAdmin::allEquipmentInfo(){

}
std::string BuildingAdmin::EquipemntInfo(int id){

}