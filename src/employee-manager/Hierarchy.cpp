//
// Created by dominik on 04.12.19.
//

#include <http-server/employee-manager/Hierarchy.h>
#include <queue>

void Hierarchy::grantPromotion(unsigned long long promoted_id,
                               unsigned long long promotedNewBossID)
{
    std::queue <std::shared_lock<std::shared_mutex>> locked_mutexes;
    std::shared_ptr<Employee> promoted_employee = findEmployee(promoted_id);
    std::shared_ptr<Employee> new_boss;

    auto promoted_employee_lock = promoted_employee->getUniqueLock();
    auto previous_employee = promoted_employee;

    int iteration = 0;
    while(previous_employee->getBoss() != nullptr)
    {
        iteration ++;
        auto current_employee = previous_employee->getBoss();
        locked_mutexes.push(current_employee->getSharedLock());
        if(previous_employee->getBoss() == current_employee)
        {   // Check if current employee is still previous boss (could have been changed while waiting for shared lock)
            locked_mutexes.back().unlock();
            locked_mutexes.pop();
            iteration --;
            continue; // Go back one iteration
        }

        if(iteration == 1)
        { // Current employee is two positions above promoted_employee, which means it will be his new boss
            new_boss = current_employee;
        }
        previous_employee=current_employee;
    }

    /* Check if current head (previous_employee) is the actual boss, if not it means
     * That in the meantine promoted_employee was assigned to
     * */

    /*GRANT PROMOTION
     * */

    while(!locked_mutexes.empty())
    {
        locked_mutexes.back().unlock();
        locked_mutexes.pop();
    }
    promoted_employee_lock.unlock();
}

void Hierarchy::removeEmployee(unsigned long long personalId)
{
    std::shared_ptr <Employee> removedOne = employees[personalId];
    std::vector <std::shared_ptr<Employee>> visited;
    visited.push_back(removedOne->boss);
    int lastvisited = 0;
    while (lastvisited < visited.size())
    { //BFS and locking
        for (auto emp: visited[lastvisited]->suboridantes)
        {
            visited.push_back(emp);
        }
        lastvisited++;
    }
    for (auto emp: removedOne->suboridantes)
    {
        emp->boss == nullptr;
        employessWithNoBoss.push_back(emp); //deleting shared pointers with him in suboridantes
    }
    visited[0]->suboridantes.remove(removedOne); //and boss
    employees.erase(
            personalId); //and the last one in hierarchy; now all shared pointers with removed one are delated so the object will be deleted

    for (int i = visited.size(); i >= 0; i--)
    { //here should be unlocking
        ;
    }
}