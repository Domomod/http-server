# http-server
A simple http/1.1 server implementation in c using bsd sockets.

Documenatation (generated using doxygen) can be found at:
https://domomod.github.io/http-server/html/index.html

## REST API
We are providing an exemplary REST API to test our http-server.

### Model
Provided service help's administrating locating and assinging equipment such as furniture, electronics or others in a building complex. Such equipment is stored in rooms. Building's are described as a hierarchy, where a building consisits of several floors, and the floors consist of several rooms. 

##### Building
Described by an unique index.

Contains several floors.
#### Floor
Described by an index unique within a building.

Contains several rooms.
#### Room
Described by an index unique within a floor.

Contains equipment.
#### Equipment
Described by an index unique withis the whole administration system.
Also described with one of predefined types:
`Furniture, Electronics, Other`.

### Model URIs
User can navigate in the system using following URIs
#### Accessing buildings
```
/buildings - all buildings
/buildings/{id} - concrete building
/buildings/{id}/equipment - equipment stored in all building's rooms
```

#### Accessing floors
```
/buildings/{id}/floors - all floors
/buildings/{id}/floors/{floor} - concrete floor in this concrete building
/buildings/{id}/floors/{floor}/equipment - equipment stored in all floor's rooms
```

#### Accesing rooms
```
/buildings/{id}/floors/{floor}/rooms/ - all rooms in this concrete floor
/buildings/{id}/floors/{floor}/rooms/{room_number} - concrete room in this concrete floor
/buildings/{id}/floors/{floor}/rooms/{room_number}/equipment - equipment stored in this concrete room.
```

#### Accesing equipment
```
/equipment - all the equipment stored in all the rooms
/equipment/{id} - concrete equipment
```

### HTTP Requests & Data Representation
User will recieve json representation corresponing in response to those HTTP Requets.
#### Building
When executing `GET /buildings`:
```json
{
    "link": {

        "href": "http::<server-adress>/buildings/",
        "rel": "self"
    },
    "buildings": [
        {
            "href": "http::<server-adress>/buildings//1",
            "rel": "self"
        },
        {
            "href": "http::<server-adress>/buildings//2",
            "rel": "self"
        }
    ]
}
```

When executing `GET /buildings/10`:
```json
{
    "id": 10,
    "street": "Kwiatowa 5",
    "link": {
        "href": "http::<server-adress>/buildings/10",
        "rel": "self"
    },
    "floors": [
        {
            "href": "http::<server-adress>/buildings/10/floors/0",
            "rel": "self"
        },
        {
            "href": "http::<server-adress>/buildings/10/floors/1",
            "rel": "self"
        }
    ]
}
```

When executing `GET /buildings/10/equipment`:
```json
{
    "id": 10,
    "street": "Kwiatowa 5",
    "link": {
        "href": "http::<server-adress>/buildings/10",
        "rel": "self"
    },
    "equipment": [
        {
            "id": "0",
            "type": "electronics",
            "name": "projector",
            "href": "http::<server-adress>/equipment/0",
            "rel": "equipment"
        },
        {
            "id": "3",
            "type": "electronics",
            "name": "stationary pc",
            "href": "http::<server-adress>/equipment/3",
            "rel": "equipment"
        },
        {
            "id": "10",
            "type": "furniture",
            "name": "chair",
            "href": "http::<server-adress>/equipment/10",
            "rel": "equipment"
        }
    ]
}
```
#### Floor
When executing `GET /buildings/10/floors`:
```json
{
    "link": {
        "href": "http::<server-adress>/buildings/10/floors",
        "rel": "self"
    },
    "floors": [
        {
            "href": "http::<server-adress>/buildings/10/floors/0",
            "rel": "self"
        },
        {
            "href": "http::<server-adress>/buildings/10/floors/1",
            "rel": "self"
        }
    ]
}
```

When executing `GET /buildings/10/floors/1`:
```json
{
    "id": 1,
    "link": {
        "href": "http::<server-adress>/buildings/10/floors/1",
        "rel": "self"
    },
    "rooms": [
        {
            "href": "http::<server-adress>/buildings/10/floors/1/rooms/1",
            "rel": "self"
        },
        {
            "href": "http::<server-adress>/buildings/10/floors/1/rooms/2",
            "rel": "self"
        }
    ]
}
```

When executing `GET /buildings/10/floors/3/equipment`:
```json
{
    "id": 3,
    "link": {
        "href": "http::<server-adress>/buildings/10/floors/3/equipment",
        "rel": "self"
    },
    "equipment": [
        {
            "id": "2",
            "type": "electronics",
            "name": "projector",
            "href": "/2",
            "rel": "http::<server-adress>/equipment"
        },
        {
            "id": "4",
            "type": "electronics",
            "name": "stationary pc",
            "href": "/4",
            "rel": "http::<server-adress>/equipment"
        },
        {
            "id": "14",
            "type": "furniture",
            "name": "table",
            "href": "/14",
            "rel": "http::<server-adress>/equipment"
        }
    ]
}
```

#### Room
When executing `GET /buildings/10/floors/3/rooms`:
```json
{
    "link": {
        "href": "http::<server-adress>/buildings/10/floors/3/rooms",
        "rel": "self"
    },
    "links": [
        {
            "href": "http::<server-adress>/buildings/10/floors/3/rooms/1",
            "rel": "self"
        },
        {
            "href": "http::<server-adress>/buildings/10/floors/3/rooms/2",
            "rel": "self"
        }
    ]
}
```

When executing `GET /buildings/10/floors/3/rooms/2` or `GET /buildings/10/floors/3/rooms/2/equipment`:
```json
{
    "id": 2,
    "link": {
        "href": "http::<server-adress>/buildings/10/floors/3/rooms/2",
        "rel": "self"
    },
    "equipment": [
        {
            "id": "2",
            "type": "electronics",
            "name": "projector",
            "link": {
                "href": "http::<server-adress>/equipment/2",
                "rel": "self"
            }
        },
        {
            "id": "4",
            "type": "electronics",
            "name": "stationary pc",
            "link": {
                    "href": "http::<server-adress>/equipment/4",
                    "rel": "self"
            }
        },
        {
            "id": "14",
            "type": "furniture",
            "name": "table",
            "link": {
                    "href": "http::<server-adress>/equipment/14",
                    "rel": "self"
            }
        }
    ]
}
```

#### Equipment
When executing `GET /equipment`:

```json
{
    "equipment": [
        {
            "id": "2",
            "type": "electronics",
            "name": "projector",
            "link" : {
                "href": "http::<server-adress>/equipment/2",
                "rel": "self"
            },
            "location": {
                "href": "http::<server-adress>/buildings/10/floors/1/rooms",
                "rel": "self"
            }
        },
        {
            "id": "4",
            "type": "electronics",
            "name": "stationary pc",
            "link" : {
                "href": "http::<server-adress>/equipment/4",
                "rel": "self"
            },
            "location": {
                "href": "http::<server-adress>/buildings/10/floors/1/rooms",
                "rel": "self"
            }
        }
    ]
}
```

When executing `GET /equipment/2`:

```json
{
    "id": "2",
    "type": "electronics",
    "name": "projector",
    "link" : {
        "href": "http::<server-adress>/equipment/2",
        "rel": "self"
    },
    "location": {
        "href": "http::<server-adress>/buildings/10/floors/1/rooms",
        "rel": "self"
    }
}
```
`Furniture, Electronics, Other`.
