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

     BuildingComponent(int _idx, std::string _name);
     int getIdx();
     std::string getName();
     void printInfo();
};




#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
