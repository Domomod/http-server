//
// Created by dominik on 04.12.19.
//

#ifndef HTTP_SERVER_HIERARCHY_H
#define HTTP_SERVER_HIERARCHY_H

#include <unordered_map>
#include "Employee.h"
#include <shared_mutex>
#include <vector>
class Hierarchy
{
public:
    void addEmployee(const std::shared_ptr<Employee>& employee)
    {
        std::unique_lock lock(map_mutex);
        employees.insert({employee->personalIdentityNumber, employee});
    }

    std::shared_ptr<Employee> findEmployee(unsigned long long personalId)
    {
        std::shared_lock lock(map_mutex);
        auto employee_iter = employees.find(personalId);
        if ( employee_iter == employees.end() )
            return std::shared_ptr<Employee>(nullptr);
        else
            return employee_iter->second;
    }

    void removeEmployee(unsigned long long personalId);

    void grantPromotion(unsigned long long promotedID,
                        unsigned long long promotedNewBossID);
private:
    std::shared_mutex map_mutex;
    // For my colegues: It's equivalent of a Hash Set in Java :)
    std::unordered_map<unsigned long long, std::shared_ptr<Employee>> employees;
    std::shared_ptr<Employee> boss;
    std::vector<std::shared_ptr<Employee>> employessWithNoBoss;
};



#endif //HTTP_SERVER_HIERARCHY_H
