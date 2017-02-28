#
# clog is header only
#
set(DEPS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/clog/")


#
# CARGO is header only
#
set(DEPS_INCLUDES ${DEPS_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/cargo/")

#
# SSOCK is header only
#
set(DEPS_INCLUDES ${DEPS_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/ssock/")

#
# xmlc
#
add_subdirectory(xmlc)
set(DEPS_INCLUDES ${DEPS_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/xmlc/src/")
set(DEPS_LIBRARIES ${DEPS_LIBARRIES} xmlc)

#
# return
#
set(DEPS_INCLUDES  ${DEPS_INCLUDES} PARENT_SCOPE)
set(DEPS_LIBRARIES ${DEPS_LIBRARIES} PARENT_SCOPE)

