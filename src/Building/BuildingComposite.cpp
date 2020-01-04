//
// Created by Julia on 2019-12-20.
//

#include <iostream>
#include <http-server/Building/BuildingComposite.h>

BuildingComposite::BuildingComposite(int idx, std::string name) : BuildingComponent(idx, name)
{
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

void BuildingComposite::showMyInfo( json &j)
{
 BuildingComponent::convertToJson(j);
 j["@class-name"]="BuildingComposite";
 j["idx"]=idx;
 j["name"]=name;
 j["insides start"]="{";
 for (auto build: buildingComponents)
     build->showMyInfo(j);
 j["insides end"]="}";
}

void BuildingComposite::showMyEq(json &j)
{
    for (auto build: buildingComponents)
        build->showMyEq(j);
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
    j["buildingComponents"] = buildingComponents;
}

void BuildingComposite::convertFromJson(const json &j)
{
    BuildingComponent::convertFromJson(j);
    j.at("buildingComponents").get_to(buildingComponents);
}
