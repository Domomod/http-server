//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_ROOM_H
#define HTTP_SERVER_ROOM_H


#include "BuildingComponent.h"
class Room : BuildingComponent{
private:
    float surface;
    int lampWattage;
    float cubature;
    float heating;
public:
    Room(int idx, std::string name, float surface, int lampWattage, float cubature);
    float GetSurface();
    int GetLampWattage();
    float GetCubature();
    float GetHeating();
    float LampPerMeter2();
    float HeatPerMeter3();
    std::string GetInfo();
};




#endif //HTTP_SERVER_ROOM_H
