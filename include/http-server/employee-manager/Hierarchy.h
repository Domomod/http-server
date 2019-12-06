//
// Created by dominik on 04.12.19.
//

#ifndef HTTP_SERVER_HIERARCHY_H
#define HTTP_SERVER_HIERARCHY_H

#include <unordered_map>
#include <http-server/employee-manager/Employee.h>
#include <shared_mutex>
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

    void removeEmployee(unsigned long long personalId)
    {
        std::unique_lock lock(map_mutex);
        employees.erase(personalId);
    }

    void grantPromotion(unsigned long long promotedID,
                        unsigned long long promotedNewBossID,
                        unsigned long long subordinatesNewBossID)
    {
        
    }
private:
    std::shared_mutex map_mutex;
    // For my colegues: It's equivalent of a Hash Set in Java :)
    std::unordered_map<unsigned long long, std::shared_ptr<Employee>> employees;
};


#endif //HTTP_SERVER_HIERARCHY_H
