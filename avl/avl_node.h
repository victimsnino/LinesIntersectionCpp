#pragma once
#include <memory>

template<typename KeyType>
struct Node;

template<typename KeyType>
struct BaseNode
{
public:
    BaseNode(KeyType value)
        : m_value(value) {}

    virtual ~BaseNode() = default;

    const BaseNode* GetLeftNode() const { return m_left.get(); }
    const BaseNode* GetRightNode() const { return m_right.get(); }
    const KeyType&  GetValue() const { return m_value; }

protected:
    std::unique_ptr<Node<KeyType>>& GetLeftNodeRef() { return m_left; }
    std::unique_ptr<Node<KeyType>>& GetRightNodeRef() { return m_right; }

private:
    const KeyType                  m_value;
    std::unique_ptr<Node<KeyType>> m_left;
    std::unique_ptr<Node<KeyType>> m_right;
};

template<typename KeyType>
struct Node : public BaseNode<KeyType>
{
    using BaseNode<KeyType>::BaseNode;

    void Insert(KeyType value);

private:
    void BalanceIfNeeded();

private:
    size_t                m_height = 1;
};

template<typename KeyType>
void Node<KeyType>::Insert(KeyType value)
{
    auto& ptr = value < GetValue() ? GetLeftNodeRef() : GetRightNodeRef();
    if (ptr)
        ptr->Insert(std::move(value));
    else
        ptr = std::make_unique<Node<KeyType>>(std::move(value));

    BalanceIfNeeded();
}

template<typename KeyType>
void Node<KeyType>::BalanceIfNeeded()
{
    //m_height = std::max(m_left ? m_left->m_height : 0, m_right ? m_right->m_height : 0) + 1;
}
