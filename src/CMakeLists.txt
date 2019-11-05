# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${http_server_SOURCE_DIR}/include/http-server/*.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${http_server_SOURCE_DIR}/src/*.cpp")

message(STATUS "HEADER_LIST: ${HEADER_LIST}")
message(STATUS "SOURCE_LIST: ${SOURCE_LIST}")


# Make an automatic library - will be static or dynamic based on user setting
add_library(http_server_library ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(http_server_library PUBLIC ../include)

# This depends on (header only) boost
target_link_libraries(http_server_library PRIVATE Boost::boost)

# This depends on threads
target_link_libraries(http_server_library PRIVATE Threads::Threads)

# All users of this library will need at least C++11
target_compile_features(http_server_library PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
