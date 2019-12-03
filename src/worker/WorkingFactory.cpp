//
// Created by Julia on 2019-12-02.
//

#include "http-server/building/WorkingFactory.h"

BuildingFactory::BuildingFactory(std::string name) {
    constructedComponent=new BuildingComposite(idx, name);
}

void BuildingFactory::Reset(String name){
    constructedComponent = new BuildingComposite(idx, name);
}

void BuildingFactory::AddFloor(String name){
    idx++;
    constructedComponent.AddChild(new BuildingComposite(idx, name));
}

void BuildingFactory::AddRoom(String name, float surface, int lampWattage, float cubature){
    idx++;
    if(constructedComponent.GetChildCount() > 0){
        BuildingComposite Floor = (BuildingComposite) constructedComponent.GetLastChild();
        Floor.AddChild(new Room(idx, name, surface, lampWattage, cubature));
    }
    else{
        System.out.println("Worker not created: A worker without floors, cant have any rooms.");
    }
}

BuildingComponent BuildingFactory::GetResult(){
    return constructedComponent;
}

BuildingComponent BuildingFactory::GetExamplaryBuilding() {
    BuildingFactory factory = new BuildingFactory("Building");

    factory.AddFloor("Floor1");
    factory.AddRoom("Room11", 10, 4, 10);
    factory.AddRoom("Room12", 8, 6, 7);
    factory.AddRoom("Room13", 8, 6, 7);

    factory.AddFloor("Floor2");
    factory.AddRoom("Room21", 14, 6, 7);
    factory.AddRoom("Room22", 14, 6,7);

    factory.AddFloor("Floor3");
    factory.AddRoom("Room31", 14, 6, 7);
    factory.AddRoom("Room32", 8, 6,7);
    factory.AddRoom("Room33", 4, 6,7);

    return factory.GetResult();
}