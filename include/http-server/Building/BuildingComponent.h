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

using json = nlohmann::json;

class BuildingComponent
{
    friend class BuildingFactory;
protected:
    int idx;
    std::string name;
    std::shared_mutex guard;
public:
    BuildingComponent() = default;

    BuildingComponent(int _idx, std::string _name);

    inline std::shared_lock<std::shared_mutex> getReadLock()
    {
        return std::move(std::shared_lock<std::shared_mutex>(guard));
    };

    inline std::unique_lock<std::shared_mutex> getWriteLock()
    {
        return std::move(std::unique_lock<std::shared_mutex>(guard));
    };

    int getIdx();

    std::string getName();

    virtual void addChild(std::shared_ptr<BuildingComponent> buildingComponent)
    {
        throw ("Operation addChild not permited");
    }

    virtual std::shared_ptr<BuildingComponent> getChild(int id) = 0;



    virtual void deleteChild(int floorId)
    {
        throw HttpException(StatusCode::Method_Not_Allowed, "Operation remove child not permited");
    }

    virtual void addEquipment(std::shared_ptr<Equipment> eq)
    {
    };

    virtual void deleteEquipment(int equipmentId)
    {
    };

    virtual std::shared_ptr<Equipment> getEquipment(int equipmentId)
    {
    };

    virtual void showMyInfo( json &j);

    virtual void convertToJson(json & j)
    {
        j["idx"] = idx;
        j["name"] = name;
    }



    virtual void convertFromJson(const json & j)
    {
        j.at("idx").get_to(idx);
        j.at("name").get_to(name);
    }

    virtual void  showMyEq( json &j);
};

void to_json(json &j, const std::shared_ptr<BuildingComponent> &x);

void from_json(const json &j, std::shared_ptr<BuildingComponent> &a);

#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
