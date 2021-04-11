cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

pybind11_add_module(pyp0f p0f.cpp
    ../src/api.c
    ../src/fp_http.c
    ../src/fp_mtu.c
    ../src/fp_tcp.c
    ../src/p0f.c
    ../src/process.c
    ../src/readfp.c)

set_target_properties(pyp0f PROPERTIES OUTPUT_NAME p0f)
target_link_libraries(pyp0f PRIVATE p0f)

enable_testing()
add_test(NAME pytest
    COMMAND ${Python3_EXECUTABLE} -m pytest ${CMAKE_SOURCE_DIR}/tests)

set_tests_properties(pytest
    PROPERTIES ENVIRONMENT PYTHONPATH=${CMAKE_BINARY_DIR}/py)
