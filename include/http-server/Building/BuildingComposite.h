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
public:
    BuildingComposite() = default;

    BuildingComposite(int idx, std::string name);

    void add_child(std::shared_ptr<BuildingComponent> buildingComponent) override;

    void add_equipment(std::shared_ptr<Equipment> eq) override;

    void delete_child(int floorId) override;

    void delete_equipment(int equipmentId) override;

    std::shared_ptr<BuildingComponent> get_child(int id) override;

    std::shared_ptr<Equipment> get_equipment(int equipmentId) override;

protected:
    void create_structure_json(json &j) override;

    void create_equipment_json(json &j) override;

    void to_json(json &j) override;

    void from_json(const json &j) override;

private:
    std::vector<std::shared_ptr<BuildingComponent>> buildingComponents;
};


#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
