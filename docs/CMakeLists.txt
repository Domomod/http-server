set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${http_server_SOURCE_DIR}/include/http-server/*.h")
set(DOXYGEN_OUT ${http_server_SOURCE_DIR}/Doxyfile)
doxygen_add_docs(docs
        ${HEADER_LIST}
        "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
        WORKING_DIRECTORY ${http_server_SOURCE_DIR}/docs
        )
