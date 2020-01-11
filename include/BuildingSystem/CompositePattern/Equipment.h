//
// Created by Julia on 2019-12-22.
//

#ifndef HTTP_SERVER_OBJECT_H
#define HTTP_SERVER_OBJECT_H

#include <string>
#include <mutex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace BuildingSystem
{
    class Equipment
    {
        friend void to_json(json &j, const std::shared_ptr<Equipment> &e);
        friend void from_json(const json &j, std::shared_ptr<Equipment> &e);
    public:
        enum Type
        {
            FURNITURE, ELECTRONICS, OTHER
        };

        static int counter;
        static std::mutex counter_guard;

        /*!
         * @brief Default constructor, created object is gibberish. Load data into it by deserialzing a json object.
         */
        Equipment() = default;

        /*!
         * @brief Creates equipment, automatically assigns unique id.
         */
        Equipment(std::string _name, enum Type enumType);

        /*!
         * @brief Getter.
         * @return Equipment object's id.
         */
        int get_id();
    private:

        /*!
         * @brief Serializes object to json.
         */
        void to_json(json &j);

        /*!
         * @brief Deserializes object from json to this object. Id will be automatically generated.
         */
        void from_json(const json &j);

        /*!
         * @brief Generates a unique id. Thread safe.
         */
        static int generate_id();

        Type type;
        int index;
        std::string name;
    };

/*!
 * @brief Allows Type enum serialization as string.
 */
    NLOHMANN_JSON_SERIALIZE_ENUM(Equipment::Type, {
        { Equipment::Type::FURNITURE, "furniture" },
        { Equipment::Type::ELECTRONICS, "electronics" },
        { Equipment::Type::OTHER, "other" },
    })

/*!
 * @brief Function used to provide various serialization operators by nlhomann's "Json for Modern C++".
 * @param j Json to contains a serialized equipment object.
 * @param e Equipment object to be serialized.
 */
    void to_json(json &j, const std::shared_ptr<Equipment> &e);

/*!
 * @brief Function used to provide variouse serialization operators by nlhomann's "Json for Modern C++".
 * @param j Json containging a proper serialization of an Equipment object.
 * @param e Equipment object to contain the deserialized data.
 */
    void from_json(const json &j, std::shared_ptr<Equipment> &e);
}

#endif //HTTP_SERVER_OBJECT_H
