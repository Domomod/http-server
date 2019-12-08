//
// Created by dominik on 04.12.19.
//

#include "Hierarchy.h"



void Hierarchy::grantPromotion(unsigned long long promotedID,
                    unsigned long long promotedNewBossID){
    std::vector<std::shared_ptr<Employee>> visited;
    visited.push_back(
            employees[promotedNewBossID]);
    int lastvisited=0;
    while (lastvisited<visited.size()){ //BFS and there should be also locking
        for (auto emp: visited[lastvisited]->suboridantes){
            visited.push_back(emp);
        }
        lastvisited++;
    }
    bool found=false;
    for (int i=visited.size()-1; i>=0; i--){ //Checking if the employee is on the list
        if (visited[i]->personalIdentityNumber==promotedID){
            found=true;
            lastvisited=i;
        }
    }
    if (found== false){
        std::string msg="Employee with given id isn't n x[sub] oridant of the second one; can't promote";
        throw msg;
    }
    for (auto emp: visited[lastvisited]->suboridantes){
        emp->boss== nullptr;
        employessWithNoBoss.push_back(emp);
    }
    visited[lastvisited]->suboridantes.clear();
    visited[lastvisited]->setBoss(visited[0]);
    visited.at(0)->suboridantes.push_back(visited[lastvisited]);
}

void Hierarchy::removeEmployee(unsigned long long personalId)
{
    std::shared_ptr<Employee> removedOne = employees[personalId];
    std::vector<std::shared_ptr<Employee>> visited;
    visited.push_back(removedOne->boss);
    int lastvisited=0;
    while (lastvisited<visited.size()){ //BFS and locking
        for (auto emp: visited[lastvisited]->suboridantes){
            visited.push_back(emp);
        }
        lastvisited++;
    }
    for (auto emp: removedOne->suboridantes){
        emp->boss== nullptr;
        employessWithNoBoss.push_back(emp); //deleting shared pointers with him in suboridantes
    }
    visited[0]->suboridantes.remove(removedOne); //and boss
    employees.erase(personalId); //and the last one in hierarchy; now all shared pointers with removed one are delated so the object will be deleted

    for (int i= visited.size(); i>=0; i--){ //here should be unlocking
        ;
    }
}