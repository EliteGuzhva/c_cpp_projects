######################################################################
# @author      : Nikita Guzhva (nik_finger@mail.ru)
# @file        : CMakeLists
# @created     : Thursday Aug 26, 2021 23:47:20 MSK
######################################################################

cmake_minimum_required(VERSION 3.16)
project(c_cpp_projects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(cpp_async)
add_subdirectory(gzv)
add_subdirectory(problems)
add_subdirectory(utils)
