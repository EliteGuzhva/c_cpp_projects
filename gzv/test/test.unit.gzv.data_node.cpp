#include <catch2/catch.hpp>
#include <gzv/data_node.h>

TEST_CASE("Init") {
    int* a = new int[3]{1, 2, 3};
    DataNode<int> node(a, nullptr);
}