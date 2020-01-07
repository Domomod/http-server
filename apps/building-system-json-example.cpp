//
// Created by dominik on 03.01.20.
//

#include <http-server/BuildingSystem/CompositePattern/ComponentFactory.h>
#include <http-server/BuildingSystem/CompositePattern/Component.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <memory>

using json = nlohmann::json;

using namespace BuildingSystem;

int main()
{
    std::shared_ptr<Component> building = ComponentFactory::get_example();

    json j = building;

    std::cout << j.dump(4);

    std::shared_ptr<Component> building_from_json;

    j.get_to(building_from_json);

    json json_from_building_from_json = building_from_json;

    std::cout << "\n\n======================================================\n\n"
    << json_from_building_from_json.dump(4);

    std::string j1_string = j.dump();
    std::string j2_string = json_from_building_from_json.dump();

    std::cout << "\n Are those jsons the same?\n" << (j1_string == j2_string);
}