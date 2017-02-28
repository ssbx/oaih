cmake_minimum_required (VERSION 2.6)
project (oaih)

configure_file(
    ${CMAKE_SOURCE_DIR}/Makefile.in ${CMAKE_SOURCE_DIR}/Makefile)

add_subdirectory(deps/ssock)

include_directories(
    .
    ${SSOCK_INCLUDES}
    deps/cargo
    deps/clog)

add_executable(oaih oaih.c)

target_link_libraries(oaih ${SSOCK_LIBRARIES})
