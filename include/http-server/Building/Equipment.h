//
// Created by Julia on 2019-12-22.
//

#ifndef HTTP_SERVER_OBJECT_H
#define HTTP_SERVER_OBJECT_H

#include <string>

class Equipment {
public:
    enum Type{FURNITURE, ELECTRONICS, OTHER};
    static int counter;
    Equipment(std::string _name, enum Type enumType);
    int getId();
    std::string showInfo();
private:
    Type type;
    int index;
    std::string name;
};

int Equipment::counter=0;

#endif //HTTP_SERVER_OBJECT_H
