#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "avl.h"

class ComparableObject
{
public:
    ComparableObject(double value)
        : m_value(value) {}


    friend bool operator==(const ComparableObject& lhs, const ComparableObject& rhs)
    {
        return lhs.m_value == rhs.m_value;
    }

    friend bool operator<(const ComparableObject& lhs, const ComparableObject& rhs)
    {
        return lhs.m_value < rhs.m_value;
    }

    friend bool operator>(const ComparableObject& lhs, const ComparableObject& rhs) { return rhs < lhs; }

    friend std::ostream& operator<<(std::ostream& os, const ComparableObject& obj)
    {
        return os << "ComparableObject{" << obj.m_value << "}";
    }

private:
    double      m_value;
};

TEMPLATE_TEST_CASE("AVL rotations works correct", "[avl]", int, double, ComparableObject)
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

    SECTION("Inserts and rotations")
    {
        std::vector<TestType> values;
        std::vector<TestType> values_to_add;
        std::vector<int> indexes = { 1, 0, 2 };

        auto do_test = [&](std::vector<int> indexes)
        {
            for (auto& v : values_to_add)
                tree.Insert(v);

            auto node = tree.FindNode(values[indexes[0]]);
            is_value_equal(node, values[indexes[0]]);

            auto left_node = node->GetLeft();
            is_value_equal(left_node, values[indexes[1]]);

            auto right_node = node->GetRight();
            is_value_equal(right_node, values[indexes[2]]);

            is_null(left_node->GetLeft());
            is_null(left_node->GetRight());

            is_null(right_node->GetLeft());
            is_null(right_node->GetRight());

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
    SECTION("Remove")
    {
        std::vector<TestType> values{ TestType(10) , TestType(15), TestType(20) };
        //    [15]
        //   /    \
        //[10]    [20]
        for (auto& v : values)
            tree.Insert(v);

        SECTION("Remove left child")
        {
            tree.Remove(values[0]);
            auto node = tree.FindNode(values[1]);
            is_value_equal(node, values[1]);

            auto left_node = node->GetLeft();
            is_null(left_node);

            auto right_node = node->GetRight();
            is_value_equal(right_node, values[2]);
        }
        SECTION("Remove right child")
        {
            tree.Remove(values[2]);
            auto node = tree.FindNode(values[1]);
            is_value_equal(node, values[1]);

            auto left_node = node->GetLeft();
            is_value_equal(left_node, values[0]);

            auto right_node = node->GetRight();
            is_null(right_node);
        }
        SECTION("Remove root")
        {
            tree.Remove(values[1]);
            {
                auto node = tree.FindNode(values[1]);
                is_null(node);
            }
            auto node = tree.FindNode(values[2]);
            is_value_equal(node, values[2]);

            auto left_node = node->GetLeft();
            is_value_equal(left_node, values[0]);

            auto right_node = node->GetRight();
            is_null(right_node);
        }
        SECTION("Deeper tree")
        {
            for (const auto& v : { TestType(5), TestType(13), TestType(17), TestType(30), TestType(22) })
            {
                values.push_back(v);
                tree.Insert(v);
            }
            //          [15]
            //         /    \
            //      [10]    [20]
            //      /  \    /  \
            //    [5] [13][17] [30]
            //                 /
            //               [22]

            tree.Remove(values[2]);

            auto node = tree.FindNode(values[1]);

            auto right = node->GetRight();
            is_value_equal(right, values[7]);

            is_value_equal(right->GetLeft(), values[5]);
            auto right_of_right = right->GetRight();
            is_value_equal(right_of_right, values[6]);

            is_null(right_of_right->GetLeft());
        }
    }
}