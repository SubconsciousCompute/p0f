cmake_minimum_required(VERSION 3.12)

#
# CMake configuration.
#
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#
# Project
#
project(p0f LANGUAGES C CXX)
set(P0F_VERSION 3.09b)

#
# Configuration
#
option(WITH_TOOLS "Build tools" ON) 

#
# Search dependencies
#
find_package(PCAP REQUIRED)

#
# Build configuration
#
add_definitions(-DVERSION="${P0F_VERSION}")
include_directories(${PCAP_INCLUDE_DIR})
if(WITH_TOOLS)
    add_subdirectory(tools)
endif()

#
# Targets 
#
set(P0F_CONFIG_FILE ${CMAKE_SOURCE_DIR}/p0f.fp)
add_executable(p0f p0f.c fp_http.c fp_mtu.c fp_tcp.c process.c readfp.c api.c)
target_link_libraries(p0f PRIVATE ${PCAP_LIBRARY})
add_custom_command(TARGET p0f POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${P0F_CONFIG_FILE} ${CMAKE_BINARY_DIR}
    VERBATIM)

#
# install
#
include(GNUInstallDirs)
install(TARGETS p0f RUNTIME DESTINATION bin)
install(FILES ${P0F_CONFIG_FILE} TYPE SYSCONF)
install(DIRECTORY docs/ TYPE DOC) 

#
# tests
#
enable_testing()
