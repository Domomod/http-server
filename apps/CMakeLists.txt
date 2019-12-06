add_executable(app app.cpp)
target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE http_server_library)

add_executable(employees employees.cpp)
target_compile_features(employees PRIVATE cxx_std_17)
target_link_libraries(employees PRIVATE http_server_library)
