//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPONENT_H
#define HTTP_SERVER_BUILDINGCOMPONENT_H


#include <string>
#include <memory>
#include "Equipment.h"
#include <http-server/http/exceptions/HttpException.h>
#include <http-server/http/exceptions/HttpStatusCodes.h>
#include <nlohmann/json.hpp>
#include <shared_mutex>
#include "Exceptions.h"

using json = nlohmann::json;

class BuildingComponent
{
    friend class BuildingFactory;
    friend void to_json(json &j, const std::shared_ptr<BuildingComponent> &x);
    friend void from_json(const json &j, std::shared_ptr<BuildingComponent> &a);
public:
    BuildingComponent() = default;

    BuildingComponent(int _idx, std::string _name);

    virtual void add_child(std::shared_ptr<BuildingComponent> buildingComponent) = 0;

    virtual void add_equipment(std::shared_ptr<Equipment> eq) = 0;

    virtual void delete_child(int floorId) = 0;

    virtual void delete_equipment(int equipmentId) = 0;

    virtual std::shared_ptr<BuildingComponent> get_child(int id) = 0;

    virtual std::shared_ptr<Equipment> get_equipment(int equipmentId) = 0;

    inline std::shared_lock<std::shared_mutex> get_read_lock();

    inline std::unique_lock<std::shared_mutex> get_write_lock();

    std::string get_structure_json(int i = -1);

    std::string get_equipment_json(int i = -1);

    int get_idx();

    std::string get_name();

protected:
    virtual void create_structure_json(json &j) = 0;

    virtual void create_equipment_json(json &j) = 0;

    virtual void to_json(json &j);

    virtual void from_json(const json &j);

    int idx;
    std::string name;
    std::shared_mutex guard;
};


#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
