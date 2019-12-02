//
// Created by Julia on 2019-12-02.
//

#ifndef HTTP_SERVER_BUILDINGCOMPONENT_H
#define HTTP_SERVER_BUILDINGCOMPONENT_H

#include <string>

abstract class BuildingComponent {
protected:
    int idx;
    std::string name;
public:
    abstract float GetSurface();
    abstract int GetLampWattage();
    abstract float GetCubature();
    abstract float GetHeating();
    abstract float LampPerMeter2();
    abstract float HeatPerMeter3();
    BuildingComponent(int _idx, std::string _name)
    int getIdx();
    std::string getName();
    static BuildingComponent GetExamplaryBuilding();
};


#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
