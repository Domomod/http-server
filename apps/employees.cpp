//
// Created by dominik on 05.11.19.
//

#include <http-server/employee-manager/Hierarchy.h>
#include <thread>

int main(int argc, char *argv[])
{
    Hierarchy hierarchy;
    using Pos = Employee::Position ;

    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(87103060091, Pos::CEO, "John", "Paul", 213700));              }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(87103065891, Pos::MANAGER, "Mike", "Smith", 7000));           }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(87103705091, Pos::MANAGER, "Steve", "Harder", 7600));         }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(78122349091, Pos::MANAGER, "John", "Drawer", 7000));          }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(78126300890, Pos::TEAM_MASTER, "Paul", "Miller", 6000));      }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(87522540890, Pos::TEAM_MASTER, "Paulina", "Garcia", 6000));   }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(89520497800, Pos::TEAM_MASTER, "Crsytal", "Davis", 6000));    }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(89521207002, Pos::TEAM_MASTER, "Bob", "Johnson", 6000));      }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(89501209742, Pos::TEAM_MASTER, "Frank", "Sinatra", 6000));    }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(93401205002, Pos::DEVELOPER, "Mathew", "Brown", 5000));       }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(95601224302, Pos::DEVELOPER, "John", "Johnson", 3400));       }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(96651120602, Pos::DEVELOPER, "William", "Johnson", 4000));    }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(87653420602, Pos::DEVELOPER, "Johnatan", "Paul", 4900));      }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(96651256602, Pos::DEVELOPER, "Dominik", "Smith", 6000));      }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(97651246702, Pos::DEVELOPER, "Steve", "Smith", 3000));        }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(92451246802, Pos::DEVELOPER, "Hank", "Smith", 5000));         }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(93451205602, Pos::DEVELOPER, "John", "Miller", 4500));        }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(94451303302, Pos::DEVELOPER, "Abbey", "Brown", 5500));        }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(95451220602, Pos::DEVELOPER, "Abi", "Miller", 4000));         }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(91451201602, Pos::DEVELOPER, "Abigail", "Johnson", 4500));    }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(94411200602, Pos::DEVELOPER, "Abijah", "Smith", 3500));       }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(98456200602, Pos::INTERN, "Oliver", "Garcia", 1800));         }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(94461700672, Pos::INTERN, "George", "Johnson", 1800));        }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(92351283602, Pos::INTERN, "Leo", "Garcia", 1800));            }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(93451223602, Pos::INTERN, "Alfie", "Smith", 1800));           }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(99245225602, Pos::INTERN, "Charlie", "Brown", 1800));         }).detach();
    std::thread([&] {hierarchy.addEmployee(std::make_shared<Employee>(20451105602, Pos::INTERN, "Jack", "Sinatra", 1800));          }).detach();

    return 0;
}