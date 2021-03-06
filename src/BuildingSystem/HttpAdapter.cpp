
//
// Created by Julia on 2019-12-30.
//


#include <BuildingSystem/HttpAdapter.h>

#include "BuildingSystem/HttpAdapter.h"

using namespace boost::xpressive;
using namespace HttpServer;
namespace BuildingSystem
{
    HttpAdapter::HttpAdapter(ThreadsafeFacade &buildingSystem) : buildingSystem(buildingSystem)
    {
        get_regex = sregex::compile(
                "^GET /buildings"
                "("
                /**/"/(?P<building>[[:digit:]]+)"
                /**/"("
                /*  */"/floors/(?P<floor>[[:digit:]]+)"
                /*  */"(/rooms/(?P<room>[[:digit:]]+))?"
                /**/")?"
                ")?"
                "(/(?P<what>equipment|structure))?$"
        );

        put_for_adding_regex = sregex::compile(
                "^PUT /buildings"
                "("
                /**/"/(?P<building>[[:digit:]]+)/floors"
                /**/"("
                /*  */"/(?P<floor>[[:digit:]]+)/rooms"
                /**/")?"
                ")?$"
        );

        post_regex = sregex::compile(
                "^POST /buildings/(?P<building>[[:digit:]]+)/floors/(?P<floor>[[:digit:]]+)/rooms/(?P<room>[[:digit:]]+)/equipment"
        );

        put_for_moving_regex = sregex::compile(
                "^PUT /buildings/(?P<building>[[:digit:]]+)"
                "/floors/(?P<floor>[[:digit:]]+)"
                "/rooms/(?P<room>[[:digit:]]+)"
                "/equipment/(?P<equipment>[[:digit:]]+)"
                "\\?destination="
                "/buildings/(?P<destBuilding>[[:digit:]]+)"
                "/floors/(?P<destFloor>[[:digit:]]+)"
                "/rooms/(?P<destRoom>[[:digit:]]+)"
                "$"
        );

        delete_regex = sregex::compile(
                "^DELETE /buildings"
                "("
                /**/"/(?P<building>[[:digit:]]+)"
                /**/"("
                /*    */"/floors/(?P<floor>[[:digit:]]+)"
                /*    */"("
                /*        */"/rooms/(?P<room>[[:digit:]]+)"
                /*        */"("
                /*            */"/equipment/(?P<equipment>[[:digit:]]+)"
                /*        */")?"
                /*   */")?"
                /**/")?"
                ")?$"
        );
    }

    void HttpAdapter::operator()(int connection_socket_descriptor)
    {
        SocketReader httpRequestReader(connection_socket_descriptor);
        ResponseBuilder httpResponseBuilder;
        while(true)
        {
            request = httpRequestReader.get_request();

            if(httpRequestReader.is_connection_ended())
            {
                break;
            }

            std::cout << "@\t\tRECIEVED A REQUEST FROM: " << connection_socket_descriptor << "\n"
                      << request.get_request_line() << "\n";

            Response response = respond_to_request();

            std::string strResponse = response.to_str();

            std::cout << "@\t\tSENDING A RESPONSE TO: " << connection_socket_descriptor << "\n"
                      << response.get_response_line() << "\n";

            write(connection_socket_descriptor, strResponse.c_str(), strResponse.size());
        }

    }

    HttpServer::Response HttpAdapter::respond_to_request()
    {
        responseBuilder.init();

        try
        {
            std::string str = request.get_request();
            smatch match_path;
            if (regex_search(str, match_path, get_regex))
            {
                respond_to_get(match_path);
            }
            else if (regex_search(str, match_path, post_regex))
            {
                respond_to_post(match_path);
            }
            else if (regex_search(str, match_path, delete_regex))
            {
                respond_to_delete(match_path);
            }
            else if (regex_search(str, match_path, put_for_adding_regex))
            {
                respond_to_put_for_adding(match_path);
            }
            else if (regex_search(str, match_path, put_for_moving_regex))
            {
                respond_to_put_for_moving(match_path);
            }
            else
            {
                responseBuilder.set_body("Request not recognized\n");
                responseBuilder.set_status_code(StatusCode::Bad_Request);
            }
        }
        catch (MyException& e)
        {
            responseBuilder.set_body(std::string(e.what()));
            responseBuilder.set_status_code(e.status_code);
        }
        catch (std::runtime_error& e)
        {
            responseBuilder.set_body(std::string(e.what()));
            responseBuilder.set_status_code(StatusCode::Internal_Server_Error);
        }
        catch (...)
        {
            responseBuilder.set_body("Can't provide more information, due to cathing an object of unnknown type.");
            responseBuilder.set_status_code(StatusCode::Internal_Server_Error);
        }

        responseBuilder.setHeaderInfo({{"Server",       {"BuildingSystem"}},
                                       {"Connection",   {"Keep-Alive"}},
                                       {"Content-Type", {"text/json"}}
                                      });
        return responseBuilder.getResponse();
    }

    void HttpAdapter::respond_to_put_for_adding(const smatch &match_path)
    {
        int source_building = to_int(match_path, "building");
        int source_floor = to_int(match_path, "floor");

        json j = json::parse(request.get_body());

        std::shared_ptr<Component> buildingComponent = j;

        buildingSystem.add({source_building, source_floor}, buildingComponent);

        responseBuilder.set_body("Item created\n");
        responseBuilder.set_status_code(StatusCode::Created);
    }

    void HttpAdapter::respond_to_put_for_moving(const smatch &match_path)
    {
        int source_building = to_int(match_path, "building");
        int source_floor = to_int(match_path, "floor");
        int source_room = to_int(match_path, "room");
        int source_equipment = to_int(match_path, "equipment");


        int destination_building = to_int(match_path, "destBuilding");
        int destination_floor = to_int(match_path, "destFloor");
        int destination_room = to_int(match_path, "destRoom");

        std::list source({source_building, source_floor, source_room});
        std::list destination({destination_building, destination_floor, destination_room});
        if(source == destination)
            throw SourceIsDestination();

        buildingSystem.move(source_equipment, source, destination);
        responseBuilder.set_status_code(StatusCode::OK);
        responseBuilder.set_body("Item moved\n");

    }

    void HttpAdapter::respond_to_delete(const smatch &match_path)
    {
        int source_building = to_int(match_path, "building");
        int source_floor = to_int(match_path, "floor");
        int source_room = to_int(match_path, "room");
        int source_equipment = to_int(match_path, "equipment");

        buildingSystem.remove({source_building, source_floor, source_room, source_equipment});
        responseBuilder.set_body("Item deleted.\n");
        responseBuilder.set_status_code(StatusCode::OK);
        /*CO NAJMNIEJ BUILDING PODANE*/}

    void
    HttpAdapter::respond_to_post(const smatch &match_path)
    {
        int source_building = to_int(match_path, "building");
        int source_floor = to_int(match_path, "floor");
        int source_room = to_int(match_path, "room");

        json j = json::parse(request.get_body());

        std::shared_ptr<Equipment> equipment;

        equipment = j;

        buildingSystem.add({source_building, source_floor, source_room}, equipment);

        responseBuilder.set_body("Item created\n");
        responseBuilder.set_status_code(StatusCode::Created);

    }

    void HttpAdapter::respond_to_get(const smatch &match_path)
    {
        int building = to_int(match_path, "building");
        int floor = to_int(match_path, "floor");
        int room = to_int(match_path, "room");
        std::string what = match_path["what"].str();

        std::list path = {building, floor, room};
        std::string body;

        if(what.empty())
            body = buildingSystem.get_full_info(path);
        else if(what == "equipment")
            body = buildingSystem.get_equipment(path);
        else if(what == "structure")
            body = buildingSystem.get_structure(path);
        else
            throw MethodNotImplemented();

        responseBuilder.set_body(body);
        responseBuilder.set_status_code(StatusCode::OK);
    }

    int HttpAdapter::to_int(const smatch &match_path, const std::string &name) const
    {
        return atoi(match_path[name].str().c_str());
    }
}