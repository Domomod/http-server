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

std::string BuildingComposite::convertToJson(){
    std::string message="{\n\"idx\" : \""+std::to_string(idx)+"\"\n";
    message+="\"name\" : \""+name+"\"\n";
    message+="\"street\" : \""+street+"\"\n";
    message+="\"buildingComponents\" : [";
    message+="\""+buildingComponents[0]->convertToJson()+"\"";
    for (int i=1; i<buildingComponents.size();i++)
        message+=", \""+buildingComponents[i]->convertToJson()+"\"";
    message+="]\n}";
    return message;
}