set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${http_server_SOURCE_DIR}/include/http-server/*.h")

set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${doxyfile_in} ${doxyfile} @ONLY)

add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
