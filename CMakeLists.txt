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
option(WITH_ASAN  "Enable ASan (Address Sanitizer)" OFF)
option(WITH_PYTHON  "Build python extention" ON)
option(STRICT_COMPILATION  "Enable compilation in strict mode" OFF)

#
# Search dependencies
#
find_package(PCAP REQUIRED)

#
# Build configuration
#
add_definitions(-Wall)
add_definitions(-DVERSION="${P0F_VERSION}")
include_directories(${PCAP_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)

if(WITH_TOOLS)
    add_subdirectory(src/tools)
endif()

if(WITH_PYTHON)
    add_subdirectory(external/pybind11)
    add_subdirectory(py)
endif()

if(WITH_ASAN)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_EXE_LINKER_FLAGS 
        "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif(WITH_ASAN)

if(STRICT_COMPILATION)
    add_definitions(-Werror)
endif()

#
# Targets 
#
set(P0F_CONFIG_FILE ${CMAKE_SOURCE_DIR}/p0f.fp)
add_library(p0f STATIC src/fp_http.c src/fp_mtu.c src/fp_tcp.c 
    src/process.c src/readfp.c src/api.c)
target_link_libraries(p0f PRIVATE ${PCAP_LIBRARY})

add_executable(p0f-bin src/p0f.c)
set_target_properties(p0f-bin PROPERTIES OUTPUT_NAME p0f)
target_link_libraries(p0f-bin PRIVATE p0f)

add_custom_command(TARGET p0f-bin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${P0F_CONFIG_FILE} ${CMAKE_BINARY_DIR}
    VERBATIM)

#
# install
#
include(GNUInstallDirs)
install(TARGETS p0f-bin RUNTIME DESTINATION bin)
install(FILES ${P0F_CONFIG_FILE} TYPE SYSCONF)
install(DIRECTORY docs/ TYPE DOC) 

#
# tests
#
enable_testing()
