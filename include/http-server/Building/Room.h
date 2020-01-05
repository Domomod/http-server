//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_ROOM_H
#define HTTP_SERVER_ROOM_H


#include "BuildingComponent.h"
#include "Equipment.h"
#include <vector>
#include <map>
#include <memory>

class Room : public BuildingComponent{
    friend class BuildingFactory;
    friend class BuildingFactory;
public:
    Room() = default;

    Room(int idx, std::string name);

    void add_child(std::shared_ptr<BuildingComponent> buildingComponent) override
    {   throw MethodNotImplemented();   }

    void add_equipment(std::shared_ptr<Equipment> eq) override;

    void delete_child(int floorId) override
    {   throw MethodNotImplemented();   }

    void delete_equipment(int equipmentId) override;

    std::shared_ptr<BuildingComponent> get_child(int id) override;

    std::shared_ptr<Equipment> get_equipment(int equipmentId) override;

    void create_structure_json(json &j) override;

    void create_equipment_json(json &j) override;

protected:
    void to_json(json &j) override;

    void from_json(const json &j) override;

private:
    std::map<int,std::shared_ptr<Equipment>> equipment;
};



#endif //HTTP_SERVER_ROOM_H
