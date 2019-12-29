//
// Created by Julia on 2019-12-20.
//

#include "../../include/http-server/Building/BuildingFactory.h"

std::shared_ptr<BuildingComponent> BuildingFactory::GetExamplaryBuilding(){
    std::shared_ptr<BuildingComponent> building=std::make_shared<BuildingComposite>(1,"Budynek", "Ul. Ulicowa 1");
    for (int i=1; i<4;i++){
        std::shared_ptr<BuildingComponent> floor= std::make_shared<BuildingComposite>(i, "Pietro");
        for (int j=1; j<10;j++){
            std::shared_ptr<BuildingComponent> room = std::make_shared<Room>(j, "Room");
            std::shared_ptr<Equipment> eq = std::make_shared<Equipment>("lozeczko", enum Type OTHER);
            room->addEquipment(eq);
            floor->addChild(room);
        }
        building->addChild(floor);
    }
    return building
}