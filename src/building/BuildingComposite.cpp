//
// Created by Julia on 2019-12-02.
//

#include "../../include/http-server/building/BuildingComposite.h"

BuildingComposite::BuildingComposite(int idx, String name):BuildingComponent(idx, name) {
    pass;
}

BuildingComponent BuildingComposite::getComponentById(int id){
    for(BuildingComponent component : buildingComponents){
        if(component.getIdx() == id){
            return component;
        }
    }
    return null;
}
int BuildingComposite::GetChildCount(){
    return buildingComponents.size();
}

BuildingComponent BuildingComposite::GetLastChild() {
    return buildingComponents.back();
}

void BuildingComposite::AddChild(BuildingComponent buildingComponent){
    buildingComponents.push_back(buildingComponent);
}

float BuildingComposite::GetSurface() {
    float sum=0;
    for (BuildingComponent component : buildingComponents) {
        sum+=component.GetSurface();
    }
    return sum;
}

int BuildingComposite::GetLampWattage(){
    int sum=0;
    for (BuildingComponent component : buildingComponents)
        sum+=component.GetLampWattage();
    return sum;
}

float BuildingComposite::GetCubature(){
    float sum=0;
    for (BuildingComponent component : buildingComponents)
        sum+=component.GetCubature();
    return sum;
}

float BuildingComposite::GetHeating() {
    float sum=0;
    for (BuildingComponent component : buildingComponents)
        sum+=component.GetHeating();
    return sum;
}

float BuildingComposite::LampPerMeter2(){
    return this.GetLampWattage()/this.GetSurface();
}

float BuildingComposite::HeatPerMeter3() {
    return this.GetHeating()/this.GetCubature();
}

std::string BuildingComposite::UsesMoreHeatThan(float maxLevel){
    String useMoreHeat="Id Name\n";
    for (BuildingComponent component : buildingComponents)
        if (component.HeatPerMeter3()>maxLevel)
            useMoreHeat=useMoreHeat+component.getIdx()+" "+component.getName()+"\n";
    return useMoreHeat;
}
}
