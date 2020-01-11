//
// Created by Julia on 2019-12-20.
//

#ifndef HTTP_SERVER_BUILDINGCOMPOSITE_H
#define HTTP_SERVER_BUILDINGCOMPOSITE_H

#include <map>
#include <memory>
#include "Equipment.h"
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
        void add_child(std::shared_ptr<Component> child) override;

        /*!
         * @brief Throws exception as only Rooms are allowed to have equipment.
         */
        void add_equipment(std::shared_ptr<Equipment> eq) override
        {
            throw MethodNotImplemented();
        }

        /*!
         * @brief Removes a node from this composite.
         */
        void delete_child(int id) override;

        /*!
         * @brief Throws exception as only Rooms are allowed to have equipment.
         */
        void delete_equipment(int equipmentId) override
        {
            throw MethodNotImplemented();
        }

        /*!
         * @brief Finds a child with given id. May throw ResourceNotFound.
         */
        std::shared_ptr<Component> get_child(int id) override;

        /*!
         * @brief Throws exception as only Rooms are allowed to have equipment.
         */
        std::shared_ptr<Equipment> get_equipment(int equipmentId) override
        {
            throw MethodNotImplemented();
        }

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

        std::map<int, std::shared_ptr<Component>> buildingComponents;
    };


    class Floor : public Composite
    {
    public:
        Floor() = default;

        Floor(int idx, const std::string &name) : Composite(idx, name)
        {
        }

        /*!
         * @brief Adds room to the floor.
         */
        void add_child(std::shared_ptr<Component> child) override
        {
            if (typeid(*child).hash_code() != typeid(Room).hash_code())
            {
                throw UnfittingComponentGiven();
            }
            Composite::add_child(child);
        }

    protected:
        /*!
         * @brief Serializes object to json.
         */
        void to_json(json &j) override
        {
            Composite::to_json(j);
            j["@class-name"] = typeid(Floor).name();
        }

        /*!
         * @brief Deserializes object from json.
         */
        void from_json(const json &j) override
        {
            std::string type;
            try
            {
                j.at("@class-name").get_to(type);
            }
            catch (...) /*I have no idea what json class throws*/
            {
                throw IncorrectJson();
            }
            Composite::from_json(j);

            for(auto &[key, child] : buildingComponents)
            {
                if(typeid(*child).hash_code() != typeid(Room).hash_code())
                {
                    throw IllformedBuildingJsonStructure();
                }
            }
        }
    };

    class Building : public Composite
    {
    public:
        Building() = default;

        Building(int idx, const std::string &name) : Composite(idx, name)
        {
        }

        /*!
         * @brief Adds a node to this composite.
         */
        void add_child(std::shared_ptr<Component> child) override
        {
            if (typeid(*child).hash_code() != typeid(Floor).hash_code())
            {
                throw UnfittingComponentGiven();
            }
            Composite::add_child(child);
        }

    protected:
        /*!
         * @brief Serializes object to json.
         */
        void to_json(json &j) override
        {
            Composite::to_json(j);
            j["@class-name"] = typeid(Building).name();
        }

        /*!
         * @brief Deserializes object from json.
         */
        void from_json(const json &j) override
        {
            std::string type;
            try
            {
                j.at("@class-name").get_to(type);
            }
            catch (...) /*I have no idea what json class throws*/
            {
                throw IncorrectJson();
            }
            Composite::from_json(j);

            for(auto &[key, child] : buildingComponents)
            {
                if(typeid(*child).hash_code() != typeid(Floor).hash_code())
                {
                    throw IllformedBuildingJsonStructure();
                }
            }
        }
    };

    class System : public Composite
    {
    public:
        System() = default;

        System(int idx, const std::string &name) : Composite(idx, name)
        {
        }

        /*!
         * @brief Adds a node to this composite.
         */
        void add_child(std::shared_ptr<Component> child) override
        {
            if (typeid(*child).hash_code() != typeid(Building).hash_code())
            {
                throw UnfittingComponentGiven();
            }
            Composite::add_child(child);
        }

    protected:
        /*!
         * @brief Serializes object to json.
         */
        void to_json(json &j) override
        {
            Composite::to_json(j);
            j["@class-name"] = typeid(System).name();
        }

        /*!
         * @brief Deserializes object from json.
         */
        void from_json(const json &j) override
        {
            std::string type;
            try
            {
                j.at("@class-name").get_to(type);
            }
            catch (...) /*I have no idea what json class throws*/
            {
                throw IncorrectJson();
            }

            Composite::from_json(j);

            for(auto &[key, child] : buildingComponents)
            {
                if(typeid(*child).hash_code() != typeid(Building).hash_code())
                {
                    throw IllformedBuildingJsonStructure();
                }
            }
        }
    };
}


#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
