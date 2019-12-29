//
// Created by Julia on 2019-12-22.
//

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