//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPONENT_H
#define HTTP_SERVER_BUILDINGCOMPONENT_H


#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <shared_mutex>

#include "Equipment.h"
#include "BuildingSystem/Exceptions.h"

using json = nlohmann::json;

namespace BuildingSystem
{
    class Component
    {
        friend class ComponentFactory;
        friend void to_json(json &j, const std::shared_ptr<Component> &x);
        friend void from_json(const json &j, std::shared_ptr<Component> &a);
    public:
        Component() = default;

        Component(int idx, int height, std::string name);

        /*!
         * @brief Implementation schould either store recieved object or inform user about method being unsuported.
         */
        virtual void add_child(std::shared_ptr<Component> buildingComponent) = 0;

        /*!
         * @brief Implementation schould either store recieved object or inform user about method being unsuported.
         */
        virtual void add_equipment(std::shared_ptr<Equipment> eq) = 0;

        /*!
         * @brief Implementation schould either remove object with given id or inform user about method being unsuported.
         */
        virtual void delete_child(int floorId) = 0;

        /*!
         * @brief Implementation schould either remove object with given id or inform user about method being unsuported.
         */
        virtual void delete_equipment(int equipmentId) = 0;

        /*!
         * @brief Implementation schould either return object with given id or inform user about method being unsuported.
         */
        virtual std::shared_ptr<Component> get_child(int id) = 0;

        /*!
         * @brief Implementation schould either return object with given id or inform user about method being unsuported.
         */
        virtual std::shared_ptr<Equipment> get_equipment(int equipmentId) = 0;

        /*!
         * @brief Returns a shared lock associated with this object. Lock will automatically unlock on returned object destruction.
         */
        std::shared_lock<std::shared_mutex> get_read_lock();

        /*!
         * @brief Returns a unique lock associated with this object. Lock will automatically unlock on returned object destruction.
         */
        std::unique_lock<std::shared_mutex> get_write_lock();

        /*!
         * @brief Checks if all branches coming from this node are of the same length.
         */
        virtual bool is_balanced() = 0;

        /*!
         * @brief Calls create_structure_json(json &j)
         * @param i Indentation for pretty writing, use -1 to remove any redundant whitespaces.
         * @return Json representation of a node's structure stored in a string.
         */
        std::string get_structure_json(int i = -1);

        /*!
         * @brief Calls create_equipment_json(json &j)
         * @param i Indentation for pretty writing, use -1 to remove any redundant whitespaces.
          * @return Json representation of a node's equipment stored in a string.
        */
        std::string get_equipment_json(int i = -1);

        /*!
         * @brief Returns idx
         */
        int get_idx();

        int get_node_height() const;

        /*!
         * @brief Function used in process of creating a json representation of of the object subtree data, except to stored equipment.
         */
        virtual void create_structure_json(json &j) = 0;

        /*!
         * @brief Function used in process of creating a json representation of object's (and all node's below it) equipment in a vector.
         */
        virtual void create_equipment_json(json &j) = 0;

    protected:
        /*!
         * @brief Serializes object to json.
         */
        virtual void to_json(json &j);

        /*!
         * @brief Deserializes object from json.
         */
        virtual void from_json(const json &j);

        int idx;
        int node_height;
        std::string name;
        std::shared_mutex guard;
    };

    /*!
     * @brief Function used to provide various serialization operators by nlhomann's "Json for Modern C++".
     * @param j Json to contains a serialized equipment object.
     * @param x BuildingComponent object to be serialized.
     */
    void to_json(json &j, const std::shared_ptr<Component> &x);

    /*!
     * @brief Function used to provide variouse serialization operators by nlhomann's "Json for Modern C++".
     * @param j Json containging a proper serialization of an Equipment object.
     * @param x BuildingComponent object to be serialized.
     */
    void from_json(const json &j, std::shared_ptr<Component> &a);
}

#endif //HTTP_SERVER_BUILDINGCOMPONENT_H
