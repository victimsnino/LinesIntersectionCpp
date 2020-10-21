#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "dheap.h"

TEST_CASE("Dheap operations works correct", "[dheap]")
{
    dheap<int, 2> heap{};

    heap.Insert(2);
    heap.Insert(3);
    heap.Insert(4);
    heap.Insert(1);

    REQUIRE(heap.GetMinimum() == 1);
}