cmake_minimum_required(VERSION 3.12)

project(p0f LANGUAGES C CXX)
set(P0F_VERSION 3.09b)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#
# Search dependencies
#
find_package(PCAP REQUIRED)

#
# Build configuration
#
add_definitions(-DVERSION="${P0F_VERSION}")
include_directories(${PCAP_INCLUDE_DIR})

#
# Targets 
#
add_executable(p0f p0f.c fp_http.c fp_mtu.c fp_tcp.c process.c readfp.c api.c)

target_link_libraries(p0f PRIVATE ${PCAP_LIBRARY})
