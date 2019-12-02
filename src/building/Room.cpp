//
// Created by Julia on 2019-12-02.
//

#include "../../include/http-server/building/Room.h"
 Room::Room(int idx, String name, float _surface, int _lampWattage, float _cubature) :BuildingComponent(idx, name){
     surface = _surface;
     lampWattage = _lampWattage;
     cubature = _cubature;
     heating=0;
}

float Room::GetSurface() {
    return surface;
}

int Room::GetLampWattage(){
    return lampWattage;
}

int Room::GetLampWattage(){
    return lampWattage;
}

float Room::GetCubature(){
    return cubature;
}

float Room::GetHeating(){
    return heating;
}

float Room::LampPerMeter2(){
    return lampWattage/surface;
}

float Room::HeatPerMeter3(){
    return heating/cubature;
}

std::string  Room::GetInfo(){
    return "No. "+getIdx()+" name "+getName()+" surface "+surface+" cubature "+cubature+" lampWattage "+lampWattage;
}