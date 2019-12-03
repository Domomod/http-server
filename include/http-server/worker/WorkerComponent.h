//
// Created by Julia on 2019-12-02.
//

#ifndef HTTP_SERVER_BUILDINGCOMPONENT_H
#define HTTP_SERVER_BUILDINGCOMPONENT_H

#include <string>



class WorkerComponent {
protected:
    std::string pesel;
    std::string name;
    std::string lastName;
protected:
    float salary;
    enum class Position{
        CEO = 0,
        MANAGER,
        TEAM_MASTER,
        DEVELOPER,
        INTERN
    };
public:
    const std::string &getPesel() const;

    const std::string &getName() const;

    void setPesel(const std::string &pesel);

    void setName(const std::string &name);

    void setLastName(const std::string &lastName);

    void setSalary(float salary);

    const std::string &getLastName() const;

    float getSalary() const;
};


#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
