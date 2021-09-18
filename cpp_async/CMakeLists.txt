######################################################################
# @author      : Nikita Guzhva (nik_finger@mail.ru)
# @file        : CMakeLists
# @created     : Friday Sep 17, 2021 22:49:23 MSK
######################################################################

cmake_minimum_required(VERSION 3.17)
project(cpp_async)

find_package(OpenCV REQUIRED)

add_executable(cpp_async main.cpp)
target_link_libraries(cpp_async
  opencv::opencv_core
  opencv::opencv_highgui
)

