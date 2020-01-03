//insert
// Created by Julia on 2019-12-20.
//

#include <http-server/Building/Room.h>
#include <iostream>
#include <http-server/Building/BuildingComponent.h>
#include <http-server/http/exceptions/HttpException.h>

#include "../../include/http-server/Building/BuildingComponent.h"
#include "../../include/http-server/Building/BuildingComposite.h"

BuildingComponent::BuildingComponent(int _idx, std::string _name) {
    this->idx = _idx;
    this->name = _name;
}

int BuildingComponent::getIdx() {
    return idx;
}

std::string BuildingComponent::getName() {
    return name;
}

void to_json(json &j, const std::shared_ptr<BuildingComponent> &x)
{
    x->convertToJson(j);
}

#include <http-server/Building/BuildingComposite.h>
#include <http-server/Building/Room.h>
void from_json(const json &j, std::shared_ptr<BuildingComponent> &a)
{
    std::string type;
    try
    {
        j.at("@class-name").get_to(type);
        if (type == "BuildingComposite")
            a.reset(new BuildingComposite());
        if (type == "Room")
            a.reset(new Room());

        a->convertFromJson(j);
    }
    catch (...)
    {
        a.reset();
        throw std::runtime_error("Incorrect Json: Not a " + type + ".");
    }
}
