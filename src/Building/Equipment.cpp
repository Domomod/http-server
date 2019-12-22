//
// Created by Julia on 2019-12-22.
//

#include "../../include/http-server/Building/Equipment.h"

Equipment::Equipment(int id, std::string _name, enum Type enumType){
    index=id;
    name=_name;
    type=enumType;
}

int Equipment::getId() {
    return index;
}