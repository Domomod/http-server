cmake_minimum_required(VERSION 3.13)
project(http_server CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories("include")

add_executable(http_server
        tcp-server.cpp http/HttpRequest.cpp http/HttpRequest.h http/HttpParser.cpp http/HttpParser.h)

# Boost
# Find Boost headers and some static (release only) libraries
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS ...)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(http_server ${Boost_LIBRARIES})
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(http_server Threads::Threads)

