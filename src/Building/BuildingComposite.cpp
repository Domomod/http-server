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

float BuildingComposite::GetSurface() {
    float sum=0;
    for (std::shared_ptr<BuildingComponent> component : buildingComponents) {
        sum+=component->GetSurface();
    }
    return sum;
}

int BuildingComposite::GetLampWattage(){
    int sum=0;
    for (std::shared_ptr<BuildingComponent> component : buildingComponents)
        sum+=component->GetLampWattage();
    return sum;
}

float BuildingComposite::GetCubature(){
    float sum=0;
    for (std::shared_ptr<BuildingComponent> component : buildingComponents)
        sum+=component->GetCubature();
    return sum;
}

float BuildingComposite::GetHeating() {
    float sum=0;
    for (std::shared_ptr<BuildingComponent> component : buildingComponents)
        sum+=component->GetHeating();
    return sum;
}

float BuildingComposite::LampPerMeter2(){
    return this->GetLampWattage()/this->GetSurface();
}

float BuildingComposite::HeatPerMeter3() {
    return this->GetHeating()/this->GetCubature();
}

std::string BuildingComposite::UsesMoreHeatThan(float maxLevel){
    std::string useMoreHeat="Id Name\n";
    for (std::shared_ptr<BuildingComponent> component : buildingComponents)
        if (component->HeatPerMeter3()>maxLevel)
            std::cout<<"Something was found";
    return useMoreHeat;
}
