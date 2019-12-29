//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_ROOM_H
#define HTTP_SERVER_ROOM_H


#include "BuildingComponent.h"
#include "Equipment.h"
#include <vector>
#include <map>
#include <memory>

class Room : BuildingComponent{
private:
    std::map<int,std::shared_ptr<Equipment>> equipment;
public:
    Room(int idx, std::string name);

private:
    std::shared_ptr<BuildingComponent> getChild(int id) override;

public:
    void addEquipment(std::shared_ptr<Equipment> eq);
    std::shared_ptr<Equipment> getEquipment(int idx);
    void deleteEquipment(int idx);
    void addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId);
    void deleteEquipment(int eqId, int roomId, int floorId);
    std::shared_ptr<Equipment> getEquipment(int idx,int roomId, int floorId );
    std::string showMyInfo();
    std::string showMyEq();
};



#endif //HTTP_SERVER_ROOM_H
