//
// Created by dominik on 04.12.19.
//

#include <http-server/employee-manager/Employee.h>

Employee::Employee(const unsigned long long personalIdentityNumber, Employee::Position position,
                   const std::__cxx11::basic_string<char> &firstName, const std::__cxx11::basic_string<char> &lastName,
                   float salary) : personalIdentityNumber(personalIdentityNumber), position(position),
                                   firstName(firstName), lastName(lastName), salary(salary)
{
}
