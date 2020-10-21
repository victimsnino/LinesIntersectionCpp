#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "dheap.h"

#include <ostream>

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

TEMPLATE_TEST_CASE("Dheap operations works correct", "[dheap]", int, float, ComparableObject)
{
    dheap<TestType, 2> heap{};

    std::vector<double> elements{ 2.1, 3.1, 3.05, 4.3, 1.2, 10.31, 20.42 };
    for (auto value : elements)
        heap.Insert(TestType(value));

    SECTION("Top element is minimum")
    {
        INFO("Heap: " << AsString(heap));
        CHECK(heap.GetMinimumAndPop() == TestType(*std::min_element(elements.cbegin(), elements.cend())));
    }
    SECTION("All elemnts are sorted")
    {
        std::sort(elements.begin(), elements.end());
        for (auto value : elements)
        {
            CHECK(heap.GetMinimumAndPop() == TestType(value));
            UNSCOPED_INFO("After removing " << value << ": " << AsString(heap));
        }
    }
}

TEST_CASE("Make_heap works correct", "[dheap]")
{
    std::vector<ComparableObject> objects{ 1, 2, 3, 33.3, 0.5 };
    auto heap = dheap<ComparableObject, 2>::MakeHeap(objects);
    std::sort(objects.begin(), objects.end());
    for (auto& val : objects)
        CHECK(heap.GetMinimumAndPop() == val);
}