//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPOSITE_H
#define HTTP_SERVER_BUILDINGCOMPOSITE_H

#include<vector>
#include "BuildingComponent.h"
#include <memory>

class BuildingComposite : BuildingComponent{
private:
    std::vector<std::shared_ptr<BuildingComponent>> buildingComponents;

public:
    BuildingComposite(int idx, std::string name);
    std::shared_ptr<BuildingComponent> getComponentById(int id);
    int GetChildCount();
    std::shared_ptr<BuildingComponent> GetLastChild();
    void AddChild(std::shared_ptr<BuildingComponent> buildingComponent);
    float GetSurface();
    int GetLampWattage();
    float GetCubature();
    float GetHeating();
    float LampPerMeter2();
    float HeatPerMeter3();
    std::string UsesMoreHeatThan(float maxLevel);

};




#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
