project(gzv)

add_library(gzv INTERFACE)
target_include_directories(gzv INTERFACE include/)

add_subdirectory(test)
