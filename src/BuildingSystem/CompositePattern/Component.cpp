//insert
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include <BuildingSystem/CompositePattern/Room.h>
#include <BuildingSystem/CompositePattern/Composite.h>


namespace BuildingSystem
{
    Component::Component(int idx, std::string name) : idx(idx), name(name)
    {
    }

    int Component::get_idx()
    {
        return idx;
    }

    std::string Component::get_structure_json(int i)
    {
        json j;
        this->create_structure_json(j);
        return j.dump(i);
    }

    std::string Component::get_equipment_json(int i)
    {
        json j;
        this->create_equipment_json(j);
        return j.dump(i);
    }

    void Component::to_json(json &j)
    {
        j["idx"] = idx;
        j["name"] = name;
    }

    void Component::from_json(const json &j)
    {
        j.at("idx").get_to(idx);
        j.at("name").get_to(name);
    }

    std::shared_lock<std::shared_mutex> Component::get_read_lock()
    {
        return std::move(std::shared_lock<std::shared_mutex>(guard));
    }

    std::unique_lock<std::shared_mutex> Component::get_write_lock()
    {
        return std::move(std::unique_lock<std::shared_mutex>(guard));
    }

    void to_json(json &j, const std::shared_ptr<Component> &x)
    {
        x->to_json(j);
    }

    void from_json(const json &j, std::shared_ptr<Component> &a)
    {
        std::string type;
        try
        {
            j.at("@class-name").get_to(type);
            if (type == typeid(Room).name())
                a.reset(new Room());
            if (type == typeid(System).name())
                a.reset(new System());
            if (type == typeid(Floor).name())
                a.reset(new Floor());
            if (type == typeid(Building).name())
                a.reset(new Building());
        }
        catch (...)
        {
            a.reset();
            throw IncorrectJson();
        }

        a->from_json(j);
    }
}