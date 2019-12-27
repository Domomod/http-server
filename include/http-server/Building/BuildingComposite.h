//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPOSITE_H
#define HTTP_SERVER_BUILDINGCOMPOSITE_H

#include<vector>
#include "BuildingComponent.h"
#include <memory>
#include "Equipment.h"

class BuildingComposite : BuildingComponent{
private:
    std::vector<std::shared_ptr<BuildingComponent>> buildingComponents;
    std::string street;
public:
    BuildingComposite(int idx, std::string name);
    BuildingComposite(int idx, std::string name, std::string _street);
    std::shared_ptr<BuildingComponent> getComponentById(int id);
    int GetChildCount();
    std::shared_ptr<BuildingComponent> GetLastChild();
    void AddChild(std::shared_ptr<BuildingComponent> buildingComponent);
    void addEquipment(std::shared_ptr<Equipment> eq, int roomId, int floorId);

};




#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
