#pragma once

namespace dheap_utils
{
inline size_t Parent(size_t index, size_t D)
{
    return index > 0 ? (index - 1) / D : 0;
}

inline size_t LeftChild(size_t index, size_t D)
{
    return index * D + 1;
}

inline size_t RightChild(size_t index, size_t D, size_t n)
{
    return std::min(LeftChild(index, D) + D - 1, n - 1);
}
} // namespace dheap_utils
