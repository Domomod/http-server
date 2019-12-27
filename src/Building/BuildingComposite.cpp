//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include "../../include/http-server/Building/BuildingComposite.h"
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
