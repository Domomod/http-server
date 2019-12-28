//
// Created by Julia on 2019-12-28.
//

#ifndef HTTP_SERVER_BUILDINGADMIN_H
#define HTTP_SERVER_BUILDINGADMIN_H

#include <map>
#include <memory>
#include <string>
#include "BuildingComponent.h"
#include "Equipment.h"

class BuildingAdmin {
private:
    std::map<int, std::shared_ptr<BuildingComponent>> buildings;
public:
    void addBuilding(std::shared_ptr<BuildingComponent> building); //put
    void addFloor(std::shared_ptr<BuildingComponent> floor, int buildingId); //put
    void addRoom(std::shared_ptr<BuildingComponent> room, int buildingId, int floorId); //put
    void addEquipment(std::shared_ptr<Equipment> eq, int buildingId, int floorId, int roomId); //put
    void moveEquipment(int eqId, int buildingIdFrom, int floorIdFrom, int roomIdFrom, int buildingIdTo, int floorIdTo, int roomIdTo); //post
    void deleteBuilding(int id); //delete
    void deleteFloor(int buildingId, int floorId); //delete
    void deleteRoom(int buildingId, int floorId, int roomId);//delete
    void deleteEquipment(int buildingId, int floorId, int roomId, int eqId);//delete
    std::string allBuildingsInfo(); //get
    std::string buildingInfo_eq(int id); //get
    std::string buildingInfo_floor(int id);//get
    std::string floorInfo_rooms(int buildingId, int floorId );//get
    std::string floorInfo_eq(int buildingId, int floorId);//get
    std::string roomInfo(int buildingId, int floorId, int roomId);//get
    std::string roomEq(int buildingId, int floorId, int roomId);//get
    std::string allEquipmentInfo();//get
    std::string EquipemntInfo(int id); //get
};


#endif //HTTP_SERVER_BUILDINGADMIN_H
