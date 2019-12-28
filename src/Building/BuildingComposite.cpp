//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include "../../include/http-server/Building/BuildingComposite.h"
#include "../../include/http-server/Building/Room.h"
BuildingComposite::BuildingComposite(int idx, std::string name):BuildingComponent(idx, name) {
    street="";
    ;
}

BuildingComposite::BuildingComposite(int idx, std::string name, std::string _street):BuildingComponent(idx,name){
    street=_street;
}

std::shared_ptr<BuildingComponent> BuildingComposite::getComponentById(int id){
    for(std::shared_ptr<BuildingComponent> component : buildingComponents){
        if(component->getIdx() == id){
            return component;
        }
    }
    return nullptr;
}
int BuildingComposite::GetChildCount(){
    return buildingComponents.size();
}

std::shared_ptr<BuildingComponent> BuildingComposite::GetLastChild() {
    return buildingComponents.back();
}

void BuildingComposite::AddChild(std::shared_ptr<BuildingComponent> buildingComponent){
    buildingComponents.push_back(buildingComponent);
}

void BuildingComposite::addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId){
 if (street==""){  //It means that this is floor
     for (auto room : buildingComponents){
         if (room->getIdx()==roomId){
             room->addEquipment(eq,roomId,floorId);
             return;
         }
     }
 } else //Full building
     for (auto floor : buildingComponents){
         if (floor->getIdx()==floorId){
             floor->addEquipment(eq,roomId,floorId);
             return;
         }
     }
}

void BuildingComposite::deleteEquipment(int eqId, int roomId, int floorId){
    if (street==""){  //It means that this is floor
        for (auto room : buildingComponents){
            if (room->getIdx()==roomId){
                room->deleteEquipment(eqId,roomId,floorId)
                return;
            }
        }
    } else //Full building
        for (auto floor : buildingComponents){
            if (floor->getIdx()==floorId){
                floor->deleteEquipment(eqId,roomId,floorId);
                return;
            }
        }
}

std::shared_ptr<Equipment> BuildingComposite::getEquipment(int idx, int roomId, int floorId){
    if (street==""){  //It means that this is floor
        for (auto room : buildingComponents){
            if (room->getIdx()==roomId){
                return room->getEquipment(idx,roomId,floorId);
            }
        }
    } else //Full building
        for (auto floor : buildingComponents){
            if (floor->getIdx()==floorId){
                return floor->getEquipment(idx,roomId,floorId);
            }
        }
    return nullptr;
}

void BuildingComposite::addFloor(std::string name, int idx){
    std::shared_ptr<BuildingComposite> floor = std::make_shared<BuildingComposite>(idx, name);
    buildingComponents.push_back(dynamic_cast<std::shared_ptr<BuildingComponent>>(floor));

}
void BuildingComposite::addRoom(int floorId, std::string name, int idx){
    if (street==""){  //It means that this is floor
        auto room = std::make_shared<Room>(idx,name);
        buildingComponents.push_back(room);

    } else //Full building
        for (auto floor : buildingComponents){
            if (floor->getIdx()==floorId){
                addRoom(floorId,name,idx);
                return;
            }
        }
        std::string message="Floor doesn't exist, you can't add a room without a floor/n";
        throw message;

}