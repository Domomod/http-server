#Created with help of https://gitlab.com/CLIUtils/modern-cmake/

cmake_minimum_required(VERSION 3.13)
project(http_server
        DESCRIPTION "A simple http server"
        LANGUAGES CXX)


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # The project version number.
    set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
    set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
    set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
    mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

    # Set c++ standard to c++20
    set(CMAKE_CXX_STANDARD 20)

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)
    # uncoment to enable testing

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

# Adds Boost::boost
find_package(Boost REQUIRED)

# Adds Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR http_server_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()