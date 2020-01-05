#include <utility>

#include <utility>

//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGFACTORY_H
#define HTTP_SERVER_BUILDINGFACTORY_H


#include <string>
#include "BuildingComposite.h"
#include "BuildingComponent.h"
#include "Room.h"
class BuildingFactory
{
private:
    std::shared_ptr<BuildingComposite> constructedComponent;
    int idx = 0;
    int floor_idx = 0;
    int room_idx = 0;
public:
    BuildingFactory();

    /*!
     * @brief Resets the factory to initial state.
     */
    void reset();

    /*!
     * @brief Adds a new floor to the constructed building.
     */
    void addFloor(const std::string &name = "");

    /*!
     * @brief Adds a new floor to the most recently added floor.
     */
    void addRoom(const std::string &name = "");

    /*!
     * @brief Adds a new equipment to the most recently added room.
     */
    void addEquipment(std::shared_ptr<Equipment> equipment);

    /*!
     * @brief Returns the constructed building and returns Factory to initial state.
     */
    std::shared_ptr<BuildingComposite> getResult(const std::string &name);

    /*!
     * @brief Creates an examplary building with floors, rooms and equipment
     * @return Pointer to root BuildingComponent of the building
     */
    static std::shared_ptr<BuildingComponent> getExample();
};


#endif //HTTP_SERVER_BUILDINGFACTORY_H
