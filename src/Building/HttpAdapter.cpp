#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//
// Created by Julia on 2019-12-30.
//


#include <http-server/Building/HttpAdapter.h>

using namespace boost::xpressive;


HttpAdapter::HttpAdapter(BuildingSystem &buildingSystem) : buildingSystem(buildingSystem)
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
            "/(?P<what>equipment|structure)"
    );
    put_regex = sregex::compile(
            "^PUT /buildings"
            "("
            /**/"/(?P<building>[[:digit:]]+)/floors"
            /**/"("
            /*  */"/(?P<floor>[[:digit:]]+)/rooms"
            /*      */"("
            /*      */"/(?P<room>[[:digit:]]+)/equipment"
            /*  */")?"
            /**/")?"
            ")?$"
    );

    post_regex = sregex::compile(
            "^POST /buildings(?P<building>[[:digit:]]+)"
            "/floors/(?P<floor>[[:digit:]]+)"
            "/rooms/(?P<room>[[:digit:]]+)"
            "/equipment/(?P<equipment>[[:digit:]]+)"
            "$"
    );
    destination_regex = sregex::compile(
            "^/buildings(?P<building>[[:digit:]]+)"
            "/floors/(?P<floor>[[:digit:]]+)"
            "/rooms/(?P<room>[[:digit:]]+)"
            "$"
    );
    delete_regex = sregex::compile(
            "^DELETE /buildings/(?P<building>[[:digit:]]+)"
            "("
            /**/"/floors/(?P<floor>[[:digit:]]+)"
            /**/"("
            /*  */"/rooms/(?P<room>[[:digit:]]+)"
            /*  */"("
            /*      */"/equipment/(?P<equipment>[[:digit:]]+)"
            /*  */")?"
            /**/")?"
            ")?$"
    );
}

void HttpAdapter::operator()(int connection_socket_descriptor)
{
    HttpRequestReader *httpRequestReader = new BsdSocket_HttpRequestReader(connection_socket_descriptor);
    HttpResponseBuilder httpResponseBuilder;
    HttpRequest request = httpRequestReader->get_request();

    std::cout << "@\t\tRECIEVED A REQUEST FROM: " << connection_socket_descriptor << "\n"
              << request.get_request_line() << "\n";

    HttpResponse response = respond_to(request);

    std::string strResponse = response.to_str();

    std::cout << "@\t\tSENDING A RESPONSE TO: " << connection_socket_descriptor << "\n"
              << response.get_response_line() << "\n";

    write(connection_socket_descriptor, strResponse.c_str(), strResponse.size());

    delete httpRequestReader;
}

HttpResponse HttpAdapter::respond_to(const HttpRequest &request)
{
    responseBuilder.init();

    std::string str = request.get_request();
    smatch match_path;
    if (regex_search(str, match_path, get_regex))
    {
        respond_to_get(match_path);
    }
    else if (regex_search(str, match_path, post_regex))
    {
        respond_to_post(request, str, match_path);
    }
    else if (regex_search(str, match_path, delete_regex))
    {
        respond_to_delete(match_path);
    }
    else if (regex_search(str, match_path, put_regex))
    {
        respond_to_put(request, match_path);

    }
    else
    {
        responseBuilder.set_body("Request not recognized\n");
        responseBuilder.set_status_code(StatusCode::Not_Implemented);
    }
    responseBuilder.setHeaderInfo({{"Server",       {"BuildingSystem"}},
                                   {"Connection",   {"Keep-Alive"}},
                                   {"Content-Type", {"text/xml"}}
                                  });
    return responseBuilder.getResponse();
}

void HttpAdapter::respond_to_put(const HttpRequest &request, const smatch &match_path)
{
    int source_building = to_int(match_path, "building");
    int source_floor = to_int(match_path, "floor");
    int source_room = to_int(match_path, "room");

    try
    {
        json j = json::parse(request.get_body());

        if (source_room != 0)
        {
            std::shared_ptr<Equipment> equipment = j;
            buildingSystem.add({source_building, source_floor, source_room}, equipment);
        }
        else
        {
            std::shared_ptr<BuildingComponent> buildingComponent = j;
            buildingSystem.add({source_building, source_floor, source_room}, buildingComponent);
        }
        responseBuilder.set_body("Item created\n");
        responseBuilder.set_status_code(StatusCode::OK);

    }
    catch (...)
    {
        responseBuilder.set_body("Something went wrong\n");
        responseBuilder.set_status_code(StatusCode::Bad_Request);
    }
}

void HttpAdapter::respond_to_delete(const smatch &match_path)
{
    int source_building = to_int(match_path, "building");
    int source_floor = to_int(match_path, "floor");
    int source_room = to_int(match_path, "room");
    int source_equipment = to_int(match_path, "equipment");
    try
    {
        buildingSystem.remove({source_building, source_floor, source_room, source_equipment});
        responseBuilder.set_body("Item deleted.\n");
        responseBuilder.set_status_code(StatusCode::OK);
    }
    catch (...)
    {
        responseBuilder.set_body("Something went wrong\n");
        responseBuilder.set_status_code(StatusCode::Bad_Request);
    }
    /*CO NAJMNIEJ BUILDING PODANE*/}

void
HttpAdapter::respond_to_post(const HttpRequest &request, const std::string &str, const smatch &match_path)
{
    auto values = request.get_field_value("destination");
    if (values.size() == 1 && values[1] != HttpMessage::NO_SUCH_KEY)
    {
        smatch match_destination;
        if (regex_search(str, match_destination, destination_regex))
        {
            int source_building = to_int(match_path, "building");
            int source_floor = to_int(match_path, "floor");
            int source_room = to_int(match_path, "room");
            int source_equipment = to_int(match_path, "equipment");


            int destination_building = to_int(match_path, "building");
            int destination_floor = to_int(match_path, "floor");
            int destination_room = to_int(match_path, "room");

            try
            {
                buildingSystem.move(source_equipment, {source_building, source_floor, source_room},
                                    {destination_building, destination_floor, destination_room});
                responseBuilder.set_status_code(StatusCode::OK);
            }
            catch (...)
            {
                responseBuilder.set_body("Equipment couldn't be moved\n");
                responseBuilder.set_status_code(StatusCode::Not_Modified);
            }
        }
        else
        {
            responseBuilder.set_body("Inproper destination path.\n");
            responseBuilder.set_status_code(StatusCode::Not_Found);
        }
    }
    else
    {
        responseBuilder.set_body("Expected a destination header, got none.\n");
        responseBuilder.set_status_code(StatusCode::Precondition_Failed);
    }
}

void HttpAdapter::respond_to_get(const smatch &match_path)
{
    int building = to_int(match_path, "building");
    int floor = to_int(match_path, "floor");
    int room = to_int(match_path, "room");
    std::__cxx11::string what = match_path["what"].str();

    try
    {
        std::string body = (what == "equipment" ? buildingSystem.get_equipment({building, floor, room}) :
                            buildingSystem.get_info({building, floor, room}));
        responseBuilder.set_body(body);
        responseBuilder.set_status_code(StatusCode::OK);
    }
    catch (...)
    {
        responseBuilder.set_body("Something went wrong\n");
        responseBuilder.set_status_code(StatusCode::Bad_Request);
    }
}

int HttpAdapter::to_int(const smatch &match_path, const std::string &name) const
{
    return atoi(match_path[name].str().c_str());
}

#pragma clang diagnostic pop