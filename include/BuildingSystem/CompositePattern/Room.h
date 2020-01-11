//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_ROOM_H
#define HTTP_SERVER_ROOM_H


#include "Component.h"
#include "Equipment.h"
#include <vector>
#include <map>
#include <memory>

namespace BuildingSystem
{
    class Room : public Component{
        friend class ComponentFactory;
        friend class ComponentFactory;
    public:
        Room() = default;

        Room(int idx, std::string name);

        /*!
         * @brief Throws an exception, as Rooms need to be leafs of Building System tree.
         */
        void add_child(std::shared_ptr<Component> buildingComponent) override
        {   throw MethodNotImplemented();   }

        /*!
         * @brief Adds equipment to the room.
         */
        void add_equipment(std::shared_ptr<Equipment> equipment) override;

        /*!
         * @brief Throws an exception, as Rooms need to be leafs of Building System tree.
         */
        void delete_child(int floorId) override
        {   throw MethodNotImplemented();   }

        /*!
         * @brief Removes equipment from room. Throws exception if no such equipment found.
         * @param equipmentId
         */
        void delete_equipment(int equipmentId) override;

        /*!
         * @brief Throws an exception, as Rooms need to be leafs of Building System tree.
         */
        std::shared_ptr<Component> get_child(int id) override
        {   throw MethodNotImplemented();   }

        /*!
         * @brief If found returns a equipment stored inside the room.
         */
        std::shared_ptr<Equipment> get_equipment(int equipmentId) override;

        /*!
         * @brief Constructs a json representation of this room (omitting stored equipment).
         * @param j reference to json constructing object.
         */
        void create_structure_json(json &j) override;

        /*!
         * @brief Appends equipment json to a json representation of a vector.
         * @param j reference to json constructing object.
         */
        void create_equipment_json(json &j) override;

    protected:
        /*!
         * @brief Serializes object to json.
         */
        void to_json(json &j) override;

        /*!
         * @brief Deserializes object from json.
         */
        void from_json(const json &j) override;

    private:
        std::map<int,std::shared_ptr<Equipment>> equipment_map;
    };
}
#endif //HTTP_SERVER_ROOM_H
