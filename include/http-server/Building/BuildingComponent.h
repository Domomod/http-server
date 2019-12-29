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


class BuildingComponent
{
    friend class BuildingFactory;
protected:
    int idx;
    std::string name;
public:
    BuildingComponent(int _idx, std::string _name);

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

    virtual std::string showMyInfo() = 0;
    virtual std::string convertToJson()=0;
    virtual std::string showMyEq() = 0;
};


#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
