#pragma once
#include <cassert>

template<typename KeyType>
struct Node
{
public:
    Node(Node<KeyType>* parent, KeyType&& value)
        : m_value(std::move(value))
        , m_parent(parent) {}

    const KeyType& GetValue() const { return m_value; }

    const Node<KeyType>* GetLeft() const { return m_left; }
    const Node<KeyType>* GetRight() const { return m_right; }

    static Node<KeyType>* Insert(Node<KeyType>* node, KeyType&& value);
    static Node<KeyType>* Remove(Node<KeyType>* node, const KeyType& value);

    static Node<KeyType>* FindNode(Node<KeyType>* node, const KeyType& value);

    static Node<KeyType>* Next(const Node<KeyType>* node);
    static Node<KeyType>* Prev(const Node<KeyType>* node);
private:
    static void           UpdateHeight(Node<KeyType>* node);
    static Node<KeyType>* BalanceIfNeeded(Node<KeyType>* node);

    static int GetHeight(Node<KeyType>* node) { return node ? node->m_height : 0; };
    static int GetDiffHeights(Node<KeyType>* node) { return GetHeight(node->m_right) - GetHeight(node->m_left); }

    static Node<KeyType>* LeftRotation(Node<KeyType>* node);
    static Node<KeyType>* RightRotation(Node<KeyType>* node);

    static Node<KeyType>* BigLeftRotation(Node<KeyType>* node);
    static Node<KeyType>* BigRightRotation(Node<KeyType>* node);

    static Node<KeyType>* FindMin(Node<KeyType>* node);
    static Node<KeyType>* FindMax(Node<KeyType>* node);

private:
    KeyType m_value;

    Node<KeyType>* m_left{};
    Node<KeyType>* m_right{};
    Node<KeyType>* m_parent{};

    int m_height = 1;
};

template<typename KeyType>
Node<KeyType>* Node<KeyType>::Insert(Node<KeyType>* node, KeyType&& value)
{
    if (!node)
        return new Node<KeyType>(node, std::move(value));

    if (value < node->m_value)
        node->m_left = Insert(node->m_left, std::move(value));
    else if (node->m_value < value)
        node->m_right = Insert(node->m_right, std::move(value));
    else
        assert(nullptr);

    return BalanceIfNeeded(node);
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::Remove(Node<KeyType>* node, const KeyType& value)
{
    if (!node)
        return nullptr;

    if (value < node->m_value)
        node->m_left = Remove(node->m_left, value);
    else if (node->m_value < value)
        node->m_right = Remove(node->m_right, value);
    else
    {
        Node<KeyType>* left_node  = node->m_left;
        Node<KeyType>* right_node = node->m_right;

        if (right_node)
        {
            Node<KeyType>* y = Next(node);
            node->m_value    = y->m_value;
            node->m_right    = Remove(node->m_right, y->m_value);
        }
        else if (left_node)
        {
            Node<KeyType>* y = Prev(node);
            node->m_value    = y->m_value;
            node->m_right    = Remove(node->m_left, y->m_value);
        }
        else
        {
            delete node;
            return nullptr;
        }
    }
    return BalanceIfNeeded(node);
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::FindNode(Node<KeyType>* node, const KeyType& value)
{
    if (!node)
        return nullptr;

    if (value < node->m_value)
        return FindNode(node->m_left, value);

    if (node->m_value < value)
        return FindNode(node->m_right, value);

    return node;
}

template<typename KeyType>
void Node<KeyType>::UpdateHeight(Node<KeyType>* node)
{
    node->m_height = std::max(GetHeight(node->m_left), GetHeight(node->m_right)) + 1;

    if (auto target = node->m_left)
        target->m_parent = node;

    if (auto target = node->m_right)
        target->m_parent = node;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::BalanceIfNeeded(Node<KeyType>* node)
{
    UpdateHeight(node);

    auto diff_heights = GetDiffHeights(node);
    if (abs(diff_heights) < 2) // all is fine
        return node;

    if (diff_heights == 2) // right > left
    {
        if (GetDiffHeights(node->m_right) >= 0) // right subtree: right >= left
            return LeftRotation(node);
        return BigLeftRotation(node);
    }
    if (GetDiffHeights(node->m_left) <= 0) // left <= right
        return RightRotation(node);
    return BigRightRotation(node);
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::LeftRotation(Node<KeyType>* node)
{
    Node<KeyType>* right_child = node->m_right;
    node->m_right              = right_child->m_left;
    right_child->m_left        = node;

    UpdateHeight(node);
    UpdateHeight(right_child);
    return right_child;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::RightRotation(Node<KeyType>* node)
{
    Node<KeyType>* left_child = node->m_left;
    node->m_left              = left_child->m_right;
    left_child->m_right       = node;

    UpdateHeight(node);
    UpdateHeight(left_child);
    return left_child;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::BigLeftRotation(Node<KeyType>* node)
{
    node->m_right = RightRotation(node->m_right);
    return LeftRotation(node);
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::BigRightRotation(Node<KeyType>* node)
{
    node->m_left = LeftRotation(node->m_left);
    return RightRotation(node);
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::FindMin(Node<KeyType>* node)
{
    while (node->m_left != nullptr)
    {
        node = node->m_left;
    }
    return node;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::FindMax(Node<KeyType>* node)
{
    while (node->m_right != nullptr)
    {
        node = node->m_right;
    }
    return node;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::Next(const Node<KeyType>* node)
{
    if (node->m_right)
        return FindMin(node->m_right);

    Node<KeyType>* parent = node->m_parent;
    while (parent != nullptr && parent->m_right == node)
    {
        node   = parent;
        parent = node->m_parent;
    }
    return parent;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::Prev(const Node<KeyType>* node)
{
    if (node->m_left)
        return FindMax(node->m_left);

    Node<KeyType>* parent = node->m_parent;
    while (parent != nullptr && parent->m_left == node)
    {
        node   = parent;
        parent = node->m_parent;
    }
    return parent;
}
