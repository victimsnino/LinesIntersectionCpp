#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "avl.h"

TEST_CASE("AVL works correct", "[avl]")
{
    AVLTree<int> tree;
    auto is_value_equal = [](const auto* node, auto value)
    {
        REQUIRE(node != nullptr);
        REQUIRE(node->GetValue() == value);
    };

    auto is_null = [](const auto* node)
    {
        REQUIRE(node == nullptr);
    };

    SECTION("Left rotation")
    {
        tree.Insert(1);
        tree.Insert(2);
        tree.Insert(3);

        auto node = tree.FindNode(2);
        is_value_equal(node, 2);

        auto left_node = node->GetLeftBaseNode();
        is_value_equal(left_node, 1);

        auto right_node = node->GetRightBaseNode();
        is_value_equal(right_node, 3);

        is_null(left_node->GetLeftBaseNode());
        is_null(left_node->GetRightBaseNode());

        is_null(right_node->GetLeftBaseNode());
        is_null(right_node->GetRightBaseNode());
    }
    SECTION("Right rotation")
    {
        tree.Insert(3);
        tree.Insert(2);
        tree.Insert(1);

        auto node = tree.FindNode(2);
        is_value_equal(node, 2);

        auto left_node = node->GetLeftBaseNode();
        is_value_equal(left_node, 1);

        auto right_node = node->GetRightBaseNode();
        is_value_equal(right_node, 3);

        is_null(left_node->GetLeftBaseNode());
        is_null(left_node->GetRightBaseNode());

        is_null(right_node->GetLeftBaseNode());
        is_null(right_node->GetRightBaseNode());
    }
    SECTION("Left big rotation")
    {
        tree.Insert(0);
        tree.Insert(2);
        tree.Insert(1);

        auto node = tree.FindNode(1);
        is_value_equal(node, 1);

        auto left_node = node->GetLeftBaseNode();
        is_value_equal(left_node, 0);

        auto right_node = node->GetRightBaseNode();
        is_value_equal(right_node, 2);

        is_null(left_node->GetLeftBaseNode());
        is_null(left_node->GetRightBaseNode());

        is_null(right_node->GetLeftBaseNode());
        is_null(right_node->GetRightBaseNode());
    }
    SECTION("Right big rotation")
    {
        tree.Insert(10);
        tree.Insert(8);
        tree.Insert(9);

        auto node = tree.FindNode(9);
        is_value_equal(node, 9);

        auto left_node = node->GetLeftBaseNode();
        is_value_equal(left_node, 8);

        auto right_node = node->GetRightBaseNode();
        is_value_equal(right_node, 10);

        is_null(left_node->GetLeftBaseNode());
        is_null(left_node->GetRightBaseNode());

        is_null(right_node->GetLeftBaseNode());
        is_null(right_node->GetRightBaseNode());
    }
}