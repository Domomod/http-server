//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_ROOM_H
#define HTTP_SERVER_ROOM_H


#include "BuildingComponent.h"
#include "Equipment.h"
#include <vector>
#include <map>

class Room : BuildingComponent{
private:
    std::map<int,std::shared_ptr<Equipment>> equipment;
public:
    Room(int idx, std::string name);
    void addEquipment(std::shared_ptr<Equipment> eq);
    std::shared_ptr<Equipment> getEquipment(int idx);
    void deleteEquipment(int idx);
    void addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId);
};



#endif //HTTP_SERVER_ROOM_H
