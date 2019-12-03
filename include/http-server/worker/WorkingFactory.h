//
// Created by Julia on 2019-12-02.
//

#ifndef HTTP_SERVER_BUILDINGFACTORY_H
#define HTTP_SERVER_BUILDINGFACTORY_H

#include <string>
#include "WorkerComposite.h"
#include "WorkerComponent.h"

class BuildingFactory {
private:
    BuildingComposite constructedComponent;
    int idx=0;
public:
    void Reset(std::string name);
    void AddFloor(std::string name);
    void AddRoom(std::string name, float surface, int lampWattage,float cubature);
    BuildingComponent GetResult();
    static BuildingComponent GetExamplaryBuilding();
    BuildingFactory(std::string name);
};


#endif //HTTP_SERVER_BUILDINGFACTORY_H
