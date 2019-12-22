//
// Created by Julia on 2019-12-20.
//

#include <http-server/Building/Room.h>
#include <iostream>
#include "../../include/http-server/Building/BuildingComponent.h"
#include "../../include/http-server/Building/BuildingComposite.h"

BuildingComponent::BuildingComponent(int _idx, std::string _name) {
    this->idx = _idx;
    this->name = _name;
}

int BuildingComponent::getIdx() {
    return idx;
}

std::string BuildingComponent::getName() {
    return name;
}



void BuildingComponent::printInfo(){
    std::cout<<"Name: "<<getName();
    std::cout<<"Surface: "<<GetSurface();
    std::cout<<"Cubature: "<<GetCubature();
    std::cout<<"Lamp per m^2: "<<LampPerMeter2();
    std::cout<<"Heat per m^3: "<<HeatPerMeter3();
}