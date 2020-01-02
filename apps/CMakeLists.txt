add_executable(app app.cpp)
target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE http_server_library)

add_executable(json json-hierarchical-example.cpp)
target_compile_features(json PRIVATE cxx_std_17)
target_link_libraries(json PRIVATE http_server_library)
