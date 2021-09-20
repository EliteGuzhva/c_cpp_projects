######################################################################
# @author      : Nikita Guzhva (nik_finger@mail.ru)
# @file        : CMakeLists
# @created     : Saturday Sep 18, 2021 22:35:48 MSK
######################################################################

project(problems)

find_package(Catch2 REQUIRED)

add_executable(problems main.cpp)
target_link_libraries(problems
  utils
  Catch2::Catch2
)

