//
// Created by Julia on 2019-12-22.
//

#ifndef HTTP_SERVER_OBJECT_H
#define HTTP_SERVER_OBJECT_H

#include <string>
#include <nlohmann/json.hpp>
#include "BuildingComponent.h"

using json = nlohmann::json;

class Equipment {
public:
    enum Type{FURNITURE, ELECTRONICS, OTHER};

    NLOHMANN_JSON_SERIALIZE_ENUM( Type , {
        {Type::FURNITURE, "furniture"},
        {Type::ELECTRONICS, "electronics"},
        {Type::OTHER, "other"},
    })

    static int counter;

    Equipment() = default;
    Equipment(std::string _name, enum Type enumType);
    int getId();
    std::string showInfo();
    void convertToJson(json &j);
    void convertFromJson(const json &j);
private:
    Type type;
    int index;
    std::string name;
};

void to_json(json &j, const std::shared_ptr<Equipment> &e);
void from_json(const json &j, std::shared_ptr<Equipment> &e);

#endif //HTTP_SERVER_OBJECT_H
