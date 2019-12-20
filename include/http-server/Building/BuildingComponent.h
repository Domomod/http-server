//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPONENT_H
#define HTTP_SERVER_BUILDINGCOMPONENT_H


#include <string>

 class BuildingComponent {
protected:
    int idx;
    std::string name;
public:
     virtual float GetSurface();
     virtual int GetLampWattage();
     virtual float GetCubature();
     virtual float GetHeating();
     virtual float LampPerMeter2();
     virtual float HeatPerMeter3();
     BuildingComponent(int _idx, std::string _name);
     int getIdx();
     std::string getName();
     static BuildingComponent GetExamplaryBuilding();
     void printInfo();
};




#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
