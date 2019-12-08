//
// Created by dominik on 04.12.19.
//

#ifndef HTTP_SERVER_EMPLOYEE_H
#define HTTP_SERVER_EMPLOYEE_H

#include <shared_mutex>
#include <list>
#include <string>


class Employee
{
public:
    enum class Position
    {
        CEO = 0,
        MANAGER,
        TEAM_MASTER,
        DEVELOPER,
        INTERN
    };

    Employee(const unsigned long long personalIdentityNumber, Position position, const std::string &firstName,
             const std::string &lastName, float salary);

    void setBoss(std::shared_ptr<Employee> _boss);
    const unsigned long long personalIdentityNumber;
    bool isEmployeeHere(unsigned long long id);
    friend class Hierarchy;

    float getSalary() const;
    float getSalaryWithSuboridantes();
    Position getPosition() const;
private:
    std::shared_ptr<Employee> boss;
    std::list<std::shared_ptr<Employee>> suboridantes;

    mutable Position position;
    mutable std::string firstName;

    mutable std::string lastName;
    mutable float salary;
};

#endif //HTTP_SERVER_EMPLOYEE_H
