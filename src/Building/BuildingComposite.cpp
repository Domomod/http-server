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

std::string BuildingComposite::showMyInfo(){
    std::string message="";
    if (street!=""){
        message+="Street "+street+"\n";
    }
    message+=name+" "+std::to_string(idx)+"\n";
    if (street=="")
        message+="This floor has "+std::to_string(buildingComponents.size())+" rooms\n";
    else
        message+="This building has "+std::to_string(buildingComponents.size())+" floors\n";
    return message;
}

std::string BuildingComposite::showMyEq(){
std::string message="Equipment \n";
for (int i=0; i<buildingComponents.size();i++)
    message+=showMyEq();
return message;
}
std::string BuildingComposite::showFloorInfo(int floorId){
if (street!="")
    return buildingComponents.at(floorId)->showFloorInfo(floorId);
std::string message="Floor "+std::to_string(idx)+", "+name+"\n";
message+="has "+std::to_string(buildingComponents.size())+" rooms\n";
}
std::string BuildingComposite::showFloorEq(int floorId){
    if (street!="")
        return buildingComponents.at(floorId)->showFloorEq(floorId);
    std::string message="Floor "+std::to_string(idx)+"\n";
    for (int i=0; i<buildingComponents.size();i++)
        message+=buildingComponents.at(i)->showMyEq();
}
std::string BuildingComposite::showRoomInfo(int floorId, int roomId){
    if (street!="")
        return buildingComponents.at(floorId)->showRoomInfo(floorId,roomId);
    return buildingComponents.at(roomId)->showMyInfo();

}
std::string BuildingComposite::showRoomEq(int floorId, int roomId){
    if (street!="")
        return buildingComponents.at(floorId)->showRoomEq(floorId,roomId);
    return buildingComponents.at(roomId)->showMyEq();
}