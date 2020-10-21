#pragma once

#include <cstdint>
#include <vector>

template<typename Type, uint32_t D>
class dheap
{
public:
    dheap() = default;

    void Insert(Type&& value);

    Type GetMinimum() const;

private:
    std::vector<size_t> m_indexes{};
    std::vector<Type>   m_values{};
};

template<typename Type, uint32_t D>
void dheap<Type, D>::Insert(Type&& value)
{
    m_values.emplace_back(std::forward<Type>(value));
    m_indexes.push_back(m_values.size() - 1);
}

template<typename Type, uint32_t D>
Type dheap<Type, D>::GetMinimum() const
{
    return m_values[m_indexes.front()];
}
