//
// Created by Julia on 2019-12-02.
//

#ifndef HTTP_SERVER_BUILDINGCOMPOSITE_H
#define HTTP_SERVER_BUILDINGCOMPOSITE_H

#include<vector>
#include "BuildingComponent.h"
class BuildingComposite : BuildingComponent{
private:
    std::vector<BuildingComponent> buildingComponents;

public:
    BuildingComposite(int idx, String name);
    BuildingComponent getComponentById(int id);
    int GetChildCount();
    BuildingComponent GetLastChild();
    void AddChild(BuildingComponent buildingComponent);
    float GetSurface();
    int GetLampWattage();
    float GetCubature();
    float GetHeating();
    float LampPerMeter2();
    float HeatPerMeter3();
    std::tring UsesMoreHeatThan(float maxLevel)

};


#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
