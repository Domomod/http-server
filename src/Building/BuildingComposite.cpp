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
                room->deleteEquipment(eqId,roomId,floorId);
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


void BuildingComposite::addFloor(std::shared_ptr<BuildingComponent> floor){
    buildingComponents.push_back(floor);
}
void BuildingComposite::addRoom(int floorId, std::shared_ptr<BuildingComponent> room){
    if (street==""){
        buildingComponents.push_back(room);
    } else{
        for (auto floor : buildingComponents)
            if (floor->getIdx()==floorId){
                addRoom(floorId,room);
                return;
            }
    }

}
void BuildingComposite::deleteFloor(int floorId){
    for (int i=0; i<buildingComponents.size(); i++){
        if (buildingComponents[i]->getIdx()==floorId){
            buildingComponents.erase(buildingComponents.begin()+i);
            return;
        }
    }

}
void BuildingComposite::deleteRoom(int floorId, int roomId){
    if (street==""){
        for (int i=0; i<buildingComponents.size(); i++){
            if (buildingComponents[i]->getIdx()==roomId){
                buildingComponents.erase(buildingComponents.begin()+i);
                return;
            }
        }
    } else{
        for (auto floor : buildingComponents)
            if (floor->getIdx()==floorId){
                deleteRoom(floorId,roomId);
                return;
            }
    }
}