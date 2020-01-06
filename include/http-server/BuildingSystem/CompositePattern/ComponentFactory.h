#include <utility>

#include <utility>

//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGFACTORY_H
#define HTTP_SERVER_BUILDINGFACTORY_H


#include <string>
#include "Composite.h"
#include "Component.h"
#include "Room.h"

namespace BuildingSystem
{
    class ComponentFactory
    {
    private:
        std::shared_ptr<Composite> constructedComponent;
        int idx = 0;
        int floor_idx = 0;
        int room_idx = 0;
    public:
        ComponentFactory();

        /*!
         * @brief Resets the factory to initial state.
         */
        void reset();

        /*!
         * @brief Adds a new floor to the constructed building.
         */
        void add_floor(const std::string &name = "");

        /*!
         * @brief Adds a new floor to the most recently added floor.
         */
        void add_room(const std::string &name = "");

        /*!
         * @brief Adds a new equipment to the most recently added room.
         */
        void add_equipment(std::shared_ptr<Equipment> equipment);

        /*!
         * @brief Returns the constructed building and returns Factory to initial state.
         */
        std::shared_ptr<Composite> get_result(const std::string &name);

        /*!
         * @brief Creates an examplary building with floors, rooms and equipment
         * @return Pointer to root BuildingComponent of the building
         */
        static std::shared_ptr<Component> get_example();
    };
}


#endif //HTTP_SERVER_BUILDINGFACTORY_H
