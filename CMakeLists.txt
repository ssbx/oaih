cmake_minimum_required (VERSION 2.6)
project (oaih)

configure_file(
    ${CMAKE_SOURCE_DIR}/Makefile.in ${CMAKE_SOURCE_DIR}/Makefile)

add_subdirectory(deps/)
include_directories(
    .
    ${DEPS_INCLUDES})

add_executable(oaih oaih.c)
