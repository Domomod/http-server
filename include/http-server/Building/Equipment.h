//
// Created by Julia on 2019-12-22.
//

#ifndef HTTP_SERVER_OBJECT_H
#define HTTP_SERVER_OBJECT_H

#include <string>

class Equipment {
private:
    enum Type{FURNITURE, ELECTRONICS, OTHER};
    Type type;
    int index;
    std::string name;
public:
    Equipment(int id, std::string _name, enum Type enumType);
    int getId();
};


#endif //HTTP_SERVER_OBJECT_H
