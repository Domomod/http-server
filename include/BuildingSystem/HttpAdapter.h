//
// Created by Julia on 2019-12-30.
//

#ifndef HTTP_SERVER_HTTPRESPONSER_H
#define HTTP_SERVER_HTTPRESPONSER_H

#include <HttpServer/Response.h>
#include <HttpServer/Request.h>
#include <HttpServer/ResponseBuilder.h>
#include <HttpServer/SocketReader.h>
#include <HttpServer/SocketReader.h>

#include "ThreadsafeFacade.h"
#include <memory>
#include <boost/xpressive/xpressive.hpp>

using boost::xpressive::sregex;
using boost::xpressive::smatch;

namespace BuildingSystem
{
    class HttpAdapter {
    private:
        ThreadsafeFacade& buildingSystem;
        HttpServer::ResponseBuilder responseBuilder;
        HttpServer::Request request;
        sregex get_regex;
        sregex post_regex;
        sregex put_regex;
        sregex destination_regex;
        sregex delete_regex;
    public:
        explicit HttpAdapter(ThreadsafeFacade &buildingSystem);

        /*!
         * @brief Handles communication with a socket, request parsing, responding and closing connection.
         */
        void operator()(int connection_socket_descriptor);

    private:
        /*!
         * @brief Responds to a http request.
         * @return Server response to given request
         */
        HttpServer::Response respond_to_request();

        /*!
         * @brief GET requests are used to gather information about system.
         * @param match_path result of a succesfull matching to a GET request regular expression.
         */
        void respond_to_get(const smatch &match_path);

        /*!
         * @brief POST requests are used to move equipment across the system.
         * @param match_path result of a succesfull matching to a POST request regular expression.
         */
        void respond_to_post(const smatch &match_path);

        /*!
         * @brief DELETE requests are used to remove a resource in the system.
         * @param match_path result of a succesfull matching to a POST request regular expression.
         */
        void respond_to_delete(const smatch &match_path);

        /*!
         * @brief PUT requests are used to insert or replace a resource in the system.
         * @param match_path result of a succesfull matching to a POST request regular expression.
         */
        void respond_to_put(const smatch &match_path);

        /*!
         * @brief Retrieves a named capture from regular expression matching result.
         * @param match_path Result of a succesfull regular expression matching.
         * @param name Name of the capture
         * return Capture value as an integer.
         */
        int to_int(const smatch &match_path, const std::string &name) const;
    };
}


#endif //HTTP_SERVER_HTTPRESPONSER_H
