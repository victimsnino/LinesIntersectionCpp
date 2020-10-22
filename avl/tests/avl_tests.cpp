#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "avl.h"

TEMPLATE_TEST_CASE("AVL rotations works correct", "[avl]", int)
{
    AVLTree<TestType> tree;
    auto is_value_equal = [](const auto* node, auto value)
    {
        INFO("Compare node with value: " << value);
        REQUIRE(node != nullptr);
        REQUIRE(node->GetValue() == value);
    };

    auto is_null = [](const auto* node)
    {
        REQUIRE(node == nullptr);
    };

    std::vector<TestType> values;
    std::vector<TestType> values_to_add;
    std::vector<int> indexes = { 1, 0, 2 };

    auto do_test = [&](std::vector<int> indexes)
    {
        for (auto& v : values_to_add)
            tree.Insert(v);

        auto node = tree.FindNode(values[indexes[0]]);
        is_value_equal(node, values[indexes[0]]);

        auto left_node = node->GetLeftBaseNode();
        is_value_equal(left_node, values[indexes[1]]);

        auto right_node = node->GetRightBaseNode();
        is_value_equal(right_node, values[indexes[2]]);

        is_null(left_node->GetLeftBaseNode());
        is_null(left_node->GetRightBaseNode());

        is_null(right_node->GetLeftBaseNode());
        is_null(right_node->GetRightBaseNode());

        is_null(tree.FindNode(4));
    };
    auto do_both_sides_test = [&]()
    {
        values_to_add = values;
        SECTION("Left Rotation")
        {
            do_test(indexes);
        }
        SECTION("Right Rotation")
        {
            std::reverse(values_to_add.begin(), values_to_add.end());
            do_test(indexes);
        }
    };
    SECTION("Small rotation")
    {
        values = { TestType(1.1),TestType(2.5), TestType(3.3112) };
        do_both_sides_test();
    }
    SECTION("Big rotation")
    {
        std::reverse(indexes.begin(), indexes.end());
        values = { TestType(0),TestType(2.5), TestType(1.1) };
        do_both_sides_test();
    }
}