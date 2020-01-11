//
// Created by Julia on 2019-12-22.
//

#include <BuildingSystem/CompositePattern/Component.h>
#include <BuildingSystem/CompositePattern/Equipment.h>
#include <BuildingSystem/CompositePattern/Equipment.h>

namespace BuildingSystem
{
    int Equipment::counter=0;
//Declaration of counter guard (otherwise linking errors would occur_
    std::mutex Equipment::counter_guard;

    Equipment::Equipment(std::string _name, enum Type enumType){
        index=generate_id();
        name=_name;
        type=enumType;
    }

    int Equipment::get_id() {
        return index;
    }

    void Equipment::to_json(json &j)
    {
        j["name"] = name;
        j["type"] = type;
    }

    void Equipment::from_json(const json &j)
    {
        index=generate_id();
        j.at("name").get_to(name);
        j.at("type").get_to(type);
    }

    void to_json(json &j, const std::shared_ptr<Equipment> &e)
    {
        e->to_json(j);
    }

    void from_json(const json &j, std::shared_ptr<Equipment> &e)
    {
        try
        {
            e.reset(new Equipment());
            e->from_json(j);
        }
        catch (...)
        {
            e.reset();
            throw IncorrectJson();
        }
    }

    int Equipment::generate_id()
    {
        std::lock_guard<std::mutex> lock(counter_guard);
        return counter++;
    }

}