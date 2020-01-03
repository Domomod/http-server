//
// Created by Julia on 2019-12-22.
//

#include <http-server/Building/BuildingComponent.h>
#include <http-server/Building/Equipment.h>

#include "../../include/http-server/Building/Equipment.h"

int Equipment::counter=0;

Equipment::Equipment(std::string _name, enum Type enumType){
    index=++counter;
    name=_name;
    type=enumType;
}

int Equipment::getId() {
    return index;
}
std::string Equipment::showInfo(){
    std::string message= std::to_string(index)+": "+name+"\n";
    return message;
}

void Equipment::convertToJson(json &j)
{
    j["index"] = index;
    j["name"] = name;
    j["type"] = type;
}

void Equipment::convertFromJson(const json &j)
{
    j.at("index").get_to(index);
    j.at("name").get_to(name);
    j.at("type").get_to(type);
}

void to_json(json &j, const std::shared_ptr<Equipment> &e)
{
    e->convertToJson(j);
}

void from_json(const json &j, std::shared_ptr<Equipment> &e)
{
    try
    {
        e.reset(new Equipment());
        e->convertFromJson(j);
    }
    catch (...)
    {
        e.reset();
        throw std::runtime_error("Incorrect Json: Not an Equipment object representation.");
    }
}