//
// Created by dominik on 05.11.19.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <http-server/http/HttpParser.h>
#include <http-server/http/HttpRequest.h>

TEST_CASE( "Quick check", "[main][parsing]" ) {
std:
string msg = "PUT /file HTTP/1.1\r\n\r\n"
             "Key: 10, 25, 6 7\r\n\r\n";
HttpRequest httpRequest = HttpParser::parse_message(msg);
std:
vector <std::sttring> values = httpRequest.getFieldValue("Key")[0];

REQUIRE( values[0]
== "10");

REQUIRE( values[1]
== "25");

REQUIRE( values[2]
== "6");

REQUIRE( values[3]
== "7");
}
