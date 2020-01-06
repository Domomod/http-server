//
// Created by dominik on 29.12.19.
//

#ifndef HTTP_SERVER_BUILDINGVISITOR_H
#define HTTP_SERVER_BUILDINGVISITOR_H

#include <memory>
#include <list>
#include <queue>
#include <shared_mutex>
#include "http-server/http/exceptions/HttpException.h"

#include "CompositePattern/Component.h"
#include "CompositePattern/Composite.h"
#include "Equipment.h"

namespace BuildingSystem
{
    class HttpAdapter;

/*!
 * @brief Facade intereface of BuildingSystem. All implemented methods are thread safe (they implement locking strategies).
 */
    class ThreadsafeFacade
    {
    private:
        std::shared_ptr<Component> root;
    public:
        ThreadsafeFacade();

        /*!
         * @brief Creates an adapter which provides access to this object via a http communication protocol.
         * Such adapters can be passed as a functor for thread behaviour.
         * @return An instance of HttpAdapter functor.
         */
        HttpAdapter get_http_adapter();

        /*!
         * @brief Searches a building tree for a node. Follows indexes given path untill zero index or end of list is encountered.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         * @return Desired node or ResourceNotFound thrown.
         */
        std::pair<std::shared_ptr<Component>, std::queue<std::shared_lock<std::shared_mutex>>>
        find(std::list<int> path);

        /*!
         * @brief Returns json representation of path specified node subtree structure.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         * @return Json as a string, no indents.
         */
        std::string get_structure(std::list<int> path);

        /*!
         * @brief Returns json representation of a table containing every piece of equipment in path specified node subtree.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         * @return Json as a string, no indents.
         */
        std::string get_equipment(std::list<int> path);

        /*!
         * @brief Returns json representation of path specified node subtree.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         * @return Json as a string, no indents.
         */
        std::string get_full_info(std::list<int> path){return "";}

        /*!
         * @brief Adds a node (Room, Floor, Building) to the system as a child of path specified node.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         * @param child Node to be inserted into the system.
         */
        void add(std::list<int> path, std::shared_ptr<Component> child);

        /*!
         * @brief Adds an equipment object to path specified node. The node must be a room othersise MethodNotImplemented will be throwb. May throw ResourceNotFound.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         * @param eq Equipment object to be inserted into the system.
         */
        void add(std::list<int> path, std::shared_ptr<Equipment> eq);

        /*!
         * @brief Removes a node (and it's subtree) from building system tree. May throw ResourceNotFound.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         */
        void remove(std::list<int> path);

        /*!
         * @brief Removes equipment object from path specified node. May throw ResourceNotFound or MethodNotImplemented.
         * @param path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         */
        void remove(int eq_id, std::list<int> path);

        /*!
         * @brief Moves equipment froum source node to destination node. May throw ResourceNotFound or MethodNotImplemented.
         * @param eq_id Index of equipment object desired to be moved.
         * @param source_path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         * @param dest_path Path od indexes in a form of list, with possibility to indicate an earlier end by a zero.
         */
        void move(int eq_id, std::list<int> source_path, std::list<int> dest_path);
    };
}


#endif //HTTP_SERVER_BUILDINGVISITOR_H
