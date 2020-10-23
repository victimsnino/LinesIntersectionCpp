#pragma once

#include <vector>
#include "dheap_utils.h"

template<typename Type>
class dheap
{
public:
    dheap(size_t D)
        : m_d(D) {}

    void Insert(Type value);

    Type GetMinimumAndPop();

    static dheap MakeHeap(size_t D, std::vector<Type> values);

    template<typename T>
    friend std::string AsString(const dheap<T>& heap);
private:
    void Emersion(size_t index);
    void Diving(size_t index);

    size_t MinChild(size_t index) const;
private:
    std::vector<Type> m_values{};
    const size_t      m_d;
};

template<typename Type>
void dheap<Type>::Insert(Type value)
{
    m_values.emplace_back(std::move(value));
    Emersion(m_values.size() - 1);
}

template<typename Type>
Type dheap<Type>::GetMinimumAndPop()
{
    auto value_to_return = m_values.front();

    m_values.front() = m_values.back();
    m_values.pop_back();

    Diving(0);
    return value_to_return;
}

template<typename Type>
dheap<Type> dheap<Type>::MakeHeap(size_t D, std::vector<Type> values)
{
    dheap<Type> heap{D};

    for (auto& value : values)
        heap.Insert(value);

    return heap;
}

template<typename T>
std::string AsString(const dheap<T>& heap)
{
    std::stringstream result{};
    std::copy(heap.m_values.cbegin(), heap.m_values.cend(), std::ostream_iterator<T>(result, ", "));
    return result.str();
}

template<typename Type>
void dheap<Type>::Emersion(size_t index)
{
    auto parent_index = dheap_utils::Parent(index, m_d);

    while (index != 0 && m_values[parent_index] > m_values[index])
    {
        std::swap(m_values[parent_index], m_values[index]);
        index        = parent_index;
        parent_index = dheap_utils::Parent(index, m_d);
    }
}

template<typename Type>
void dheap<Type>::Diving(size_t index)
{
    auto min_child_index = MinChild(index);
    while (min_child_index != 0 && m_values[index] > m_values[min_child_index])
    {
        std::swap(m_values[index], m_values[min_child_index]);
        index           = min_child_index;
        min_child_index = MinChild(index);
    }
}

template<typename Type>
size_t dheap<Type>::MinChild(size_t index) const
{
    auto left_child = dheap_utils::LeftChild(index, m_d);
    if (left_child >= m_values.size())
        return 0;

    auto right_child = dheap_utils::RightChild(index, m_d, m_values.size());

    auto begin = m_values.cbegin();
    auto itr   = std::min_element(begin + left_child, begin + right_child + 1);
    return std::distance(begin, itr);
}
