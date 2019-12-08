//
// Created by dominik on 04.12.19.
//

#include "Employee.h"

Employee::Employee(const unsigned long long personalIdentityNumber, Employee::Position position,
                   const std::basic_string<char> &firstName, const std::basic_string<char> &lastName,
                   float salary) : personalIdentityNumber(personalIdentityNumber), position(position),
                                   firstName(firstName), lastName(lastName), salary(salary)
{
}

bool Employee::isEmployeeHere(unsigned long long id) {
    if (personalIdentityNumber==id)
        return true; //I'm this employee
    for (auto emp: suboridantes)
        if (emp->isEmployeeHere(id))
            return true; //My subordinant is this employee
    return false;
}

void Employee::setBoss(std::shared_ptr<Employee> _boss){
    boss=_boss;
}

Employee::Position Employee::getPosition() const {
    return position;
}

float Employee::getSalary() const {
    return salary;
}

float Employee::getSalaryWithSuboridantes() {
    float salaries=salary;
    for(auto emp:suboridantes)
        salaries+=emp->getSalaryWithSuboridantes();
    return salaries;
}
