//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPONENT_H
#define HTTP_SERVER_BUILDINGCOMPONENT_H


#include <string>
#include "Equipment.h"

class BuildingComponent {
protected:
    int idx;
    std::string name;
public:
     BuildingComponent(int _idx, std::string _name);
     int getIdx();
     std::string getName();
     void printInfo();
     virtual void addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId){};
    virtual void deleteEquipment(int eqId, int roomId, int floorId){};
    virtual std::shared_ptr<Equipment> getEquipment(int idx, int roomId, int floorId){};
    virtual void addFloor(std::string name, int idx);
    virtual void addRoom(int floorId,std::string name, int idx);
};




#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
