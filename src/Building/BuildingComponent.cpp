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

BuildingComponent BuildingComponent::GetExamplaryBuilding() {
    std::shared_ptr<BuildingComposite> budynek = new std::shared_ptr<BuildingComposite?(1, "Budynek");
    BuildingComposite pietro1 = new BuildingComposite(2, "Pietro1");
    pietro1.AddChild(new Room(3, "Poko1", 10, 10, 10));
    pietro1.AddChild(new Room(4, "Poko1", 10, 10, 10));

    BuildingComposite pietro2 = new BuildingComposite(5, "Pietro2");
    pietro2.AddChild(new Room(6, "Poko1", 10, 10, 10));
    pietro2.AddChild(new Room(7, "Poko1", 10, 10, 10));

    BuildingComposite pietro3 = new BuildingComposite(10, "Pietro3");
    pietro3.AddChild(new Room(9, "Poko1", 10, 10, 10));
    pietro3.AddChild(new Room(10, "Poko1", 10, 10, 10));

    BuildingComposite pietro4 = new BuildingComposite(11, "Pietro4");
    pietro4.AddChild(new Room(12, "Poko1", 10, 10, 10));
    pietro4.AddChild(new Room(13, "Poko1", 10, 10, 10));

    budynek.AddChild(pietro1);
    budynek.AddChild(pietro2);
    budynek.AddChild(pietro3);
    budynek.AddChild(pietro4);

    return budynek;
}

void BuildingComponent::printInfo(){
    std::cout<<"Name: "<<getName();
    std::cout<<"Surface: "<<GetSurface();
    std::cout<<"Cubature: "<<GetCubature();
    std::cout<<"Lamp per m^2: "<<LampPerMeter2();
    std::cout<<"Heat per m^3: "<<HeatPerMeter3();
}