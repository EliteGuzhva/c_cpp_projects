######################################################################
# @author      : Nikita Guzhva (nik_finger@mail.ru)
# @file        : CMakeLists
# @created     : Friday Sep 17, 2021 22:49:23 MSK
######################################################################

project(cpp_async)

add_executable(cpp_async main.cpp)
target_link_libraries(cpp_async utils)