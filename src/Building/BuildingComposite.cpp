//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include "../../include/http-server/Building/BuildingComposite.h"
BuildingComposite::BuildingComposite(int idx, std::string name):BuildingComponent(idx, name) {
    ;
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
