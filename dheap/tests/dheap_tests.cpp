#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "dheap.h"

TEST_CASE("Dheap operations works correct", "[dheap]")
{
    dheap<int, 2> heap{};

    std::vector<int> elements{ 2, 3, 4, 1, 10, 20 };
    for (int value : elements)
        heap.Insert(value);

    UNSCOPED_INFO("Init" << heap.AsString());

    SECTION("Top element is minimum")
    {
        REQUIRE(heap.GetMinimumAndPop() == *std::min_element(elements.cbegin(), elements.cend()));
    }
    SECTION("All elemnts are sorted")
    {
        std::sort(elements.begin(), elements.end());
        for (auto value : elements)
        {
            REQUIRE(heap.GetMinimumAndPop() == value);
            UNSCOPED_INFO("After removing " << value << ": " << heap.AsString());
        }
    }
}