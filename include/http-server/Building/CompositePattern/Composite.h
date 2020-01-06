//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPOSITE_H
#define HTTP_SERVER_BUILDINGCOMPOSITE_H

#include <vector>
#include <memory>
#include "http-server/Building/Equipment.h"
#include "Component.h"
#include "Room.h"

namespace BuildingSystem
{
    class Composite : public Component
    {
        friend class ComponentFactory;
    public:
        Composite() = default;

        Composite(int idx, std::string name);

        /*!
         * @brief Adds a node to this composite.
         */
        void add_child(std::shared_ptr<Component> buildingComponent) override;

        /*!
         * @brief Throws exception as only Rooms are allowed to have equipment.
         */
        void add_equipment(std::shared_ptr<Equipment> eq) override
        {   throw MethodNotImplemented();   }

        /*!
         * @brief Removes a node from this composite.
         */
        void delete_child(int floorId) override;

        /*!
         * @brief Throws exception as only Rooms are allowed to have equipment.
         */
        void delete_equipment(int equipmentId) override
        {   throw MethodNotImplemented();   }

        /*!
         * @brief Finds a child with given id. May throw ResourceNotFound.
         */
        std::shared_ptr<Component> get_child(int id) override;

        /*!
         * @brief Throws exception as only Rooms are allowed to have equipment.
         */
        std::shared_ptr<Equipment> get_equipment(int equipmentId) override
        {   throw MethodNotImplemented();   }

        /*!
         * @brief Constructs a json representation of this node subtree structure.
         * @param j reference to json constructing object.
         */
        void create_structure_json(json &j) override;

        /*!
         * @brief Aggregates equipment in this node's subtree to a json representation of an array.
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
        std::vector<std::shared_ptr<Component>> buildingComponents;
    };
}


#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
