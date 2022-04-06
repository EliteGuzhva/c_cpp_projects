project(gzv_test)

find_package(Catch2 REQUIRED)

add_executable(test.unit.gzv.data_node
    test.unit.gzv.data_node.cpp
    test.unit.gzv.main.cpp
)
target_link_libraries(test.unit.gzv.data_node
    gzv
    Catch2::Catch2
)
