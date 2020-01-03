//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPOSITE_H
#define HTTP_SERVER_BUILDINGCOMPOSITE_H

#include<vector>
#include "BuildingComponent.h"
#include "Room.h"
#include <memory>
#include "Equipment.h"

class BuildingComposite : public BuildingComponent
{
    friend class BuildingFactory;
private:
    std::vector<std::shared_ptr<BuildingComponent>> buildingComponents;
    std::string street;


public:
    BuildingComposite() = default;

    BuildingComposite(int idx, std::string name);

    BuildingComposite(int idx, std::string name, std::string _street);

    void addChild(std::shared_ptr<BuildingComponent> buildingComponent) override;

    std::shared_ptr<BuildingComponent> getChild(int id) override;

    void deleteChild(int floorId) override;

    void addEquipment(std::shared_ptr<Equipment> equipmentId) override;

    void deleteEquipment(int equipmentId) override;

    std::shared_ptr<Equipment> getEquipment(int equipmentId) override;

    std::string showMyInfo() override;

    std::string showMyEq() override;

    void convertToJson(json & j) override;

    void convertFromJson(const json &j) override;
};


#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
