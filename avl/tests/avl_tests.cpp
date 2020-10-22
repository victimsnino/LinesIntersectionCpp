#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "avl.h"

TEST_CASE("AVL tree works correct", "[avl]")
{
    AVLTree<int> tree;
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);

    auto node = tree.FindNode(2);
    REQUIRE(node != nullptr);
    REQUIRE(node->GetValue() == 2);

    auto left_node = node->GetLeftNode();
    REQUIRE(left_node != nullptr);
    REQUIRE(left_node->GetValue() == 1);

    auto right_node = node->GetRightNode();
    REQUIRE(right_node != nullptr);
    REQUIRE(right_node->GetValue() == 3);
}