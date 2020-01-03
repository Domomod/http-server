//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include <http-server/Building/BuildingComposite.h>

BuildingComposite::BuildingComposite(int idx, std::string name) : BuildingComponent(idx, name)
{
    street = "";
}

BuildingComposite::BuildingComposite(int idx, std::string name, std::string _street) : BuildingComponent(idx, name)
{
    street = _street;
}

void BuildingComposite::addChild(std::shared_ptr<BuildingComponent> buildingComponent)
{
    buildingComponents.push_back(buildingComponent);
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
    std::string message = std::to_string(idx)+", "+name+"\n";
    if (street != "")
    {
        message += "Street " + street + "\n";
    }
   for (auto buildingcomponent: buildingComponents){
       message+="\t"+buildingcomponent->showMyInfo();
   }
    return message;
}

std::string BuildingComposite::showMyEq()
{
    std::string message="Equipment in "+std::to_string(idx)+"\n";
    for (auto buildingcomponent: buildingComponents){
        message+="\t"+buildingcomponent->showMyEq();
    }
    return message;
}

void BuildingComposite::addEquipment(std::shared_ptr<Equipment> equipmentId)
{   throw HttpException(StatusCode ::Bad_Request ,"Operation permitted only on rooms");  }

void BuildingComposite::deleteEquipment(int equipmentId)
{   throw HttpException(StatusCode ::Bad_Request, "Operation permitted only on rooms");  }

std::shared_ptr<Equipment> BuildingComposite::getEquipment(int equipmentId)
{   throw HttpException(StatusCode ::Bad_Request, "Operation permitted only on rooms");  }

void BuildingComposite::convertToJson(json & j)
{
    BuildingComponent::convertToJson(j);
    j["@class-name"] = "BuildingComposite";
    j["street"] = street;
    j["buildingComponents"] = buildingComponents;
}

void BuildingComposite::convertFromJson(const json &j)
{
    BuildingComponent::convertFromJson(j);
    j.at("street").get_to(street);
    j.at("buildingComponents").get_to(buildingComponents);
}
