//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include <http-server/Building/BuildingComposite.h>

BuildingComposite::BuildingComposite(int idx, std::string name) : BuildingComponent(idx, name)
{
    street = "";;
}

BuildingComposite::BuildingComposite(int idx, std::string name, std::string _street) : BuildingComponent(idx, name)
{
    street = _street;
}

std::shared_ptr<BuildingComponent> BuildingComposite::getChild(int id)
{
    for (std::shared_ptr<BuildingComponent> component : buildingComponents)
    {
        if (component->getIdx() == id)
        {
            return component;
        }
    }
    return nullptr;
}

void BuildingComposite::deleteChild(int floorId)
{
    for (int i = 0; i < buildingComponents.size(); i++)
    {
        if (buildingComponents[i]->getIdx() == floorId)
        {
            buildingComponents.erase(buildingComponents.begin() + i);
            return;
        }
    }

}

std::string BuildingComposite::showMyInfo()
{
    std::string message = "";
    if (street != "")
    {
        message += "Street " + street + "\n";
    }
    message += name + " " + std::to_string(idx) + "\n";
    if (street == "")
        message += "This floor has " + std::to_string(buildingComponents.size()) + " rooms\n";
    else
        message += "This building has " + std::to_string(buildingComponents.size()) + " floors\n";
    return message;
}

std::string BuildingComposite::showMyEq()
{
    std::string message = "Equipment \n";
    for (int i = 0; i < buildingComponents.size(); i++)
        message += showMyEq();
    return message;
}
