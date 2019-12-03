//
// Created by Julia on 2019-12-02.
//

#include "http-server/building/WorkerComponent.h"

const std::string &WorkerComponent::getPesel() const {
    return pesel;
}

const std::string &WorkerComponent::getName() const {
    return name;
}

const std::string &WorkerComponent::getLastName() const {
    return lastName;
}

float WorkerComponent::getSalary() const {
    return salary;
}

void WorkerComponent::setPesel(const std::string &pesel) {
    WorkerComponent::pesel = pesel;
}

void WorkerComponent::setName(const std::string &name) {
    WorkerComponent::name = name;
}

void WorkerComponent::setLastName(const std::string &lastName) {
    WorkerComponent::lastName = lastName;
}

void WorkerComponent::setSalary(float salary) {
    WorkerComponent::salary = salary;
}
