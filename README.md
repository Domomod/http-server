# http-server
Simple HTTP/1.0 server implementation in modern C++. This project comes with an examplary
side-project, a RESTful service.

Documenatation (generated using doxygen) can be found at:
https://domomod.github.io/http-server/html/index.html

UML diagrams can be found at:
https://domomod.github.io/http-server/model/index.html

## Installation & Running
####Requirements
- Unix operation system (bsd sockets)
- C++17 supporting compiler
- boost library
- "Json for Modern C++"  by *nlohmann* (included)

####Compilation
Project is maintained using CMake, this mean you can use IDE like CLion to run the project.

Alternatively you can also perform those operations
```
mkdir build −dir
cd build −dir
cmake ..
make
cd apps
``` 

#### Running
To run the server type  `./app <port>`, port is optional (default is 1235). This file i located in `/build-dir/apps` folder.

If everything went succesfully, the server now waits for http requests. You can test it by sending it HTTP
requests, we propose to use Postman for it, as it's comes with a very convinient GUI. We prepared a package of 
examplary requests, ready to import into POSTMAN, the link will be posted in the *appendix*, at the end of this document.

##HTTP server overview
![](./docs/images/HttpServerDiagram.svg)
Most important part's of our server are:
- a **TCP server**, which creates a thread for every user conncetion.
  Type those lines in your code to run a server instance.
  ```
    YourHTTPAdapterImplementation adapter;
    HttpServer::Threaded_tcp_server threaded_tcp_server(port, adapter);
    threaded_tcp_server.loop();
  ```
- an **Adapter** interface, override this class to implement your's service behaviour.
- a **Repsonse Builder**, use to construct HTTP Responses. Example:
    ```
    ResponseBuilder rBuilder;
    rBuilder.set_body("Body");
    rBuilder.setHeaderInfo({{"Server",       {"BuildingSystem"}},
                            {"Connection",   {"Keep-Alive"}},
                            {"Content-Type", {"text/json"}}
                           });
    rBuilder.set_status_code(StatusCode::Internal_Server_Error);
    HttpResponse r = rBuilder.getResponse();
    write(client_socket_descriptor, r.to_str().c_str(), r.to_str().size()); 
    ```
    List of status codes can be found in *Appendix*,
- a **Request Reader**, use to retrieve a single parsed HTTP request from given connection socket. Wait's for whole request to be fully recieved.
    
    ```json5
        SocketReader httpRequestReader(connection_socket_descriptor);
        ResponseBuilder httpResponseBuilder;
        while(true)
        {
            request = httpRequestReader.get_request();

            if(httpRequestReader.is_connection_ended())
            {
                break;
            }
    ```

- a **HTTP parser**, required syntax is based on RFC7230 with one simplification. Any time RFC7230 expects a set of 
 whitespaces of any length as data separator, our parser expects one space. Each line schould be ender with `\r\n` as
 standard, with `\r\n\r\n` dividing the HTTP message from it's body. The parser itself is
 implemented as state machine. You might want to use our parser, for example to implement non blocking
 request reading routine. Here is an example, from SocketReader class, of how to use our parser.
 
     ```
        
        ... read recieved bytes to a buffer ...
        unprocessed_data += buf;
        
        /*
        HttpParser will remove part's of unprocessed_data, that it has already parsed,
        leaving the reminder that couldn't be parsed without recieving more bytes 
        from the client.
        */
        httpParser.parse_and_update_buffer(unprocessed_data);
        
        if(httpParser.is_request_ready())
        {
            return httpParser.get_request();
        }
    ```
   
   Quick note on how does the `parse_and_update_buffer` works. It break's *unprocessed_data* on every `\r\n`, parses each
   full line, and leaves the reminder in *unprocessed_data* variable. Examples:
   
   `Accept: text\r\nAccept-Language: en-US\r\nAcce` will parse `Accept: text\r\n` and `Accept-Language: en-US\r\n`, 
   leaving `Acce` in *unprocessed_data*.

   `Accept: text\r\nAccept-Language: en-US\r\n` would be parsed simmilar, but leave an empty string in *unprocessed_data*.

-   **HTTPMessage**, both requests and responds share the same interface. Here is an example, how to read a HTTP header

    ```
    std::vector<std::string> value_list 
        = httpRequest->get_field_value("Content-Length");
    if (value_list[0] == Request::NO_SUCH_KEY)
    { ... such header was not found ... }
    else
    {
        unsigned long content_length;
        std::stringstream sstream(value_list[0]);
        sstream >> content_length;
        ... process your data ...
    }
    ```
    Other example `Accept-Encoding: gzip, deflate`, such header field, contains two values. In such case `get_field_value` 
    would return a vector of size 2 `{gzip, deflate}`.
    
    As you can see all data is stored as strings. This means a malicious user,
    could send you words where you expect numbers and so on. I leave you with the responsibilty
    to check if that's the case.
#Appendix
### Quick overview of RESTful service
We prepared a simple system that helps managing building's and their resources.
We represent a building as a hierarchical structure consisting of floors, and rooms. Each room
can store any number of resources. User can create multiple buildings.

Buildings, floors and rooms are represented as nodes (rooms as leafs) in a tree structure, where
the root is an auxilary node in which building's are stored.
Each node is represented by 
- `id` - which has to be unique for all sibling's (parent node's children), 
- `name` - a string, 
- `structure` - map of children (`id` is key, leafs can't have children), there is also a requirement for parent and childern types:
    - root can only store buildings
    - buildings can only store floors
    - floors can only store rooms
    
Rooms can't store any node but they can store equipment wich is represented by:
- `name` - a string,
- `type` - enum (`FURNITURE`, `ELECTRONICS`, `OTHER`)


### Accesing node and equipment
`/` - root node

`/buildings/1` - building *1* 

`/buildings/1/floors/1` - floor *1* of building *1*

`/buildings/1/floors/1/rooms/1` - floor*1*

`/buildings/1/rooms/1/equipment/0` - first equipment in room's list (indexed from 0, ordered as inserted) 

### Possible operations
#### Retrieving information
- **Get structure** - get structure, inform's which nodes belong to which parent's
    
    Example:
    
    ```http request
    GET 127.0.0.1:1235/buildings/1/structure
    ```
                        
    Result:
    
    ```json5
    {
        "idx": 1,
        "name": "Ul. Ulicowa 1",
        "structure": [
            {
                "idx": 1,
                "name": "Floor",
                "structure": [
                    {
                        "idx": 1,
                        "name": "Room"
                    },
                    {
                        "idx": 2,
                        "name": "Room"
                    },
                    ... other roooms ...
                ]
            },
            ... other floors ...
        ]
    }
    ```
- **Get equipment** - get equipment (aggregated) stored in given 
resource
    
    Example:
    
    ```http request
    GET 127.0.0.1:1235/buildings/1/floors/1/equipment
    ```
                        
    Result:
    
    ```json5
    [
        {
            "name": "bed",
            "type": "other"
        },
        ... other pieces of equipment ...
    ]
    ```
  
            
- **Get json** - get json representation of system resource
    
    Example:
    
    ```http request
    GET 127.0.0.1:1235/buildings/1/floors/1/equipment
    ```
                        
    Result:
    
    ```json5
    {
        "@class-name": "N14BuildingSystem6SystemE",
        "buildingComponents": [
            [
                1,
                {
                    "@class-name": "N14BuildingSystem8BuildingE",
                    "buildingComponents": [
                        [
                            1,
                            {
                                "@class-name": "N14BuildingSystem5FloorE",
                                "buildingComponents": [
                                    [
                                        1,
                                        {
                                            "@class-name": "N14BuildingSystem4RoomE",
                                            "equipment": [
                                                [
                                                    0,
                                                    {
                                                        "name": "bed",
                                                        "type": "other"
                                                    }
                                                ],
                                                ... other pieces of equipment ...
                                            ],
                                            "idx": 3,
                                            "name": "Room"
                                        }
                                    ],
                                    ... other rooms ...
                                ],
                                "idx": 2,
                                "name": "Floor"
                            }
                        ],
                        ... other floors ...
                    ],
                    "idx": 1,
                    "name": "Ul. Ulicowa 1"
                }
            ],
            ... other buildings ...
        ],
        "idx": 0,
        "name": "System root"
    }
                
    ```
  
          
            
#### Adding data
- **Add buidling/floor/room**
    
    This operation is not idempotent. Sending two identical requests will cause an error status code to be send as a response.

    Example:    
    ```
    POST 127.0.0.1:1235/buildings/1/floors/1/rooms
    ```
    
    Body:
    ```json5
    {
        "@class-name": "N14BuildingSystem4RoomE",
        "equipment": [
            [
                0,
                {
                    "name": "bed",
                    "type": "other"
                }
            ]
        ],
        "idx": 1,
        "name": "Room"
    }
    ```
- **Add equipment**

    This operation is idempotent, sending identical request's will result in adding two identical pieces of equipment to the system.
    
    Example:
    ```
    POST 127.0.0.1:1235/buildings/1/floors/1/rooms/1/equipment
    ```
    
    Body:
    ```json5
    {
        "index": 2,
        "name": "bed",
        "type": 2
    }
    ```
    
####Deleting resources   
-   **Remove all data**

    Example:
    ```
    DELETE 127.0.0.1:1235/buildings
    ```
        
-   **Remove specific resource:**
    
    Example:
    ```
    DELETE 127.0.0.1:1235/buildings/1/floors/1/rooms/1
    ```
    
####Other operations
-   **Moving equipment between rooms**

    Example:
    ```
    PUT 127.0.0.1:1235/buildings/1/floors/1/rooms/1/equipment/0?destination=/buildings/1/floors/1/rooms/2
    ```
###Status Codes
- Continue,                     
- Switching_Protocols,          
- OK,                           
- Created,                      
- Accepted,                     
- Non_Authoritative_Information,
- No_Content,                   
- Reset_Content,                
- Partial_Content,              
- Multiple_Choices,             
- Moved_Permanently,            
- Found,                        
- See_Other,                    
- Not_Modified,                 
- Use_Proxy,                    
- Temporary_Redirect,           
- Bad_Request,                  
- Unauthorized,                 
- Payment_Required,             
- Forbidden,                    
- Not_Found,                    
- Method_Not_Allowed,           
- Not_Acceptable,               
- Proxy_Authentication_Required,
- Request_Time_out,             
- Conflict,                     
- Gone,                         
- Length_Required,              
- Precondition_Failed,          
- Request_Entity_Too_Large,     
- Request_URI_Too_Large,        
- Unsupported_Media_Type,       
- Requested_range_not_satisfiab,
- Expectation_Failed,           
- Unprocessable_Entity          
- Internal_Server_Error,        
- Not_Implemented,              
- Bad_Gateway,                  
- Service_Unavailable,          
- Gateway_Time_out,             
- HTTP_Version_not_supported   

###Request's for Postman app
You can import our ready to send requests into your Postman app. They are stored in `PostmanCollection.json` file in main directory of this repo. 
#
Thank you for reading our README