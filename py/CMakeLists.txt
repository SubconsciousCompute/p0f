cmake_minimum_required(VERSION 3.12)

find_package(pybind11 REQUIRED)

pybind11_add_module(p0f ${SRCS})
