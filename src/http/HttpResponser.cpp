//
// Created by Julia on 2019-12-30.
//

#include "../../include/http-server/http/HttpResponser.h"
#include <list>
HttpResponser::HttpResponser(std::shared_ptr<BuildingSystem> building){
    buildingSystem=building;
    responseBuilder=new HttpResponseBuilder();
}

HttpResponse HttpResponser::createResponse(std::shared_ptr<HttpRequest> request){
    responseBuilder.init();


    using namespace boost::xpressive;

    sregex get_regex = sregex::compile(
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

    sregex put_regex = sregex::compile(
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

    sregex post_regex = sregex::compile(
            "^POST /buildings(?P<building>[[:digit:]]+)"
            "/floors/(?P<floor>[[:digit:]]+)"
            "/rooms/(?P<room>[[:digit:]]+)"
            "/equipment/(?P<equipment>[[:digit:]]+)"
            "$"
    );

    sregex destination_regex = sregex::compile(
            "^/buildings(?P<building>[[:digit:]]+)"
            "/floors/(?P<floor>[[:digit:]]+)"
            "/rooms/(?P<room>[[:digit:]]+)"
            "$"
    );

    sregex delete_regex = sregex::compile(
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

    std::string str = request.getRequest();
    smatch match_path;
    if (regex_search(str, match_path, get_regex))
    {
        int building = std::atoi(match_path["building"].str().c_str());
        int floor = std::atoi(match_path["floor"].str().c_str());
        int room = std::atoi(match_path["room"].str().c_str());
        std::string what = match_path["what"].str();
        /*ZAWSZE PODANE JEST WHAT*/

        try {

        }
        catch (...){
            responseBuilder.setBody("Something wrong\n");
            responseBuilder.setStatusCode(StatusCode::Bad_Request);
            responseBuilder.setHeaderInfo({
                                                  {"Server",       {"Test"}},
                                                  {"Connection",   {"close"}},
                                                  {"Content-Type", {"text/xml"}}
                                          });
        }


    }
    else if (regex_search(str, match_path, post_regex))
    {
        auto values = request.getFieldValue("destination");
        if (values.size() == 1 && values[0] != HttpRequest::NO_SUCH_KEY)
        {
            smatch match_destination;
            if (regex_search(str, match_destination, destination_regex))
            {
                int source_building = std::atoi(match_path["building"].str().c_str());
                int source_floor = std::atoi(match_path["floor"].str().c_str());
                int source_room = std::atoi(match_path["room"].str().c_str());
                int source_equipment = std::atoi(match_path["equipment"].str().c_str());

                int destination_building = std::atoi(match_destination["building"].str().c_str());
                int destination_floor = std::atoi(match_destination["floor"].str().c_str());
                int destination_room = std::atoi(match_destination["room"].str().c_str());

                /*W OBU PRZYPADKACH ZAWSZE WSZYSTKO PODANE*/
                try{
                    std::list<int> From;
                    std::list<int> To;
                    From.push_back(source_building);
                    From.push_back(source_floor);
                    From.push_back(source_room);
                    To.push_back(destination_building);
                    To.push_back(destination_floor);
                    To.push_back(destination_room);
                    buildingSystem->move(CO?, From,To); //CO?
                    responseBuilder.setStatusCode(StatusCode::OK);
                    responseBuilder.setHeaderInfo({
                                           {"Server",       {"Test"}},
                                           {"Connection",   {"close"}},
                                           {"Content-Type", {"text/xml"}}
                                   })
                }
                catch (...){
                    responseBuilder.setBody("Couldn't move this element.\n");
                    responseBuilder.setStatusCode(StatusCode::Not_Modified);
                    responseBuilder.setHeaderInfo({
                                           {"Server",       {"Test"}},
                                           {"Connection",   {"close"}},
                                           {"Content-Type", {"text/xml"}}
                                   });
                }
            }
            else
            {
                responseBuilder.setBody("Destination is inproper.\n");
                responseBuilder.setStatusCode(StatusCode::Not_Found);
                responseBuilder.setHeaderInfo({
                                                      {"Server",       {"Test"}},
                                                      {"Connection",   {"close"}},
                                                      {"Content-Type", {"text/xml"}}
                                              });
                /*DESTINATION IS GARBAGE*/
            }
        }
        else
        {
            responseBuilder.setBody("Destination wasn't given.\n");
            responseBuilder.setStatusCode(StatusCode::Precondition_Failed);
            responseBuilder.setHeaderInfo({
                                                  {"Server",       {"Test"}},
                                                  {"Connection",   {"close"}},
                                                  {"Content-Type", {"text/xml"}}
                                          });
            /*DESTINATION NOT GIVEN*/
        }
    }
    else if (regex_search(str, match_path, delete_regex))
    {
        int source_building = std::atoi(match_path["building"].str().c_str());
        int source_floor = std::atoi(match_path["floor"].str().c_str());
        int source_room = std::atoi(match_path["room"].str().c_str());
        int source_equipment = std::atoi(match_path["equipment"].str().c_str());
        try {
            std::list<int> toDestroy;
            toDestroy.push_back(source_building);
            if (source_floor!=0){
                toDestroy.push_back(source_floor);
                if (source_room!=0)
                {
                    toDestroy.push_back(source_room);
                    if (source_equipment!=0)
                        toDestroy.push_back(source_equipment);
                }
            }
            buildingSystem->remove(toDestroy);
            responseBuilder.setBody("Item deleted.\n");
            responseBuilder.setStatusCode(StatusCode::Ok);
            responseBuilder.setHeaderInfo({
                                                  {"Server",       {"Test"}},
                                                  {"Connection",   {"close"}},
                                                  {"Content-Type", {"text/xml"}}
                                          });

        }
        catch (...){
            responseBuilder.setBody("Something wrong\n");
            responseBuilder.setStatusCode(StatusCode::Bad_Request);
            responseBuilder.setHeaderInfo({
                                                  {"Server",       {"Test"}},
                                                  {"Connection",   {"close"}},
                                                  {"Content-Type", {"text/xml"}}
                                          });
        }

        /*CO NAJMNIEJ BUILDING PODANE*/
    }
    else if (regex_search(str, match_path, put_regex))
    {
        int source_building = std::atoi(match_path["building"].str().c_str());
        int source_floor = std::atoi(match_path["floor"].str().c_str());
        int source_room = std::atoi(match_path["room"].str().c_str());
        int source_equipment = std::atoi(match_path["equipment"].str().c_str());
        /*JEŚLI NIC NIE PODANE DODAJEMY BUDYNEK
         *JEŚLI PODANY JEST BUDYNEK TO DODAJEMY PIĘTRO
         *JEŚLI PODANY JEST BUDYNEK I PIĘTRO DODAJEMY POKÓJ*/
       try{
           std::list<int> create;
           if (source_building!=0){
                create.push_back(source_building);
                if (source_floor!=0){
                    create.push_back(source_floor);
                    if(source_room!=0){
                        create.push_back(source_room);
                        if (source_equipment!=0)
                            create.push_back(source_equipment);
                    }
                }
           }
           buildingSystem->add(create, CO?); //CO?
           responseBuilder.setBody("Item created\n");
           responseBuilder.setStatusCode(StatusCode::Ok);
           responseBuilder.setHeaderInfo({
                                                 {"Server",       {"Test"}},
                                                 {"Connection",   {"close"}},
                                                 {"Content-Type", {"text/xml"}}
                                         });
       }
       catch(...){
           responseBuilder.setBody("Something wrong\n");
           responseBuilder.setStatusCode(StatusCode::Bad_Request);
           responseBuilder.setHeaderInfo({
                                                 {"Server",       {"Test"}},
                                                 {"Connection",   {"close"}},
                                                 {"Content-Type", {"text/xml"}}
                                         });
       }
    }

    return responseBuilder.getResponse();
}
