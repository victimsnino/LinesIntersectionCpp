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

    virtual ~BaseNode()
    {
        delete m_left;
        delete m_right;
    }

    const BaseNode* GetLeftBaseNode() const { return m_left; }
    const BaseNode* GetRightBaseNode() const { return m_right; }
    const KeyType&  GetValue() const { return m_value; }

protected:
    Node<KeyType>*& GetLeftNode() { return m_left; }
    Node<KeyType>*& GetRightNode() { return m_right; }

private:
    const KeyType  m_value;
    Node<KeyType>* m_left  = nullptr;
    Node<KeyType>* m_right = nullptr;
};

template<typename KeyType>
struct Node : public BaseNode<KeyType>
{
    using BaseNode<KeyType>::BaseNode;

    Node* Insert(KeyType value);
private:
    Node* BalanceIfNeeded();
    void  UpdateHeight();

    Node* RotateLeft();
    Node* RotateRight();

    int GetDiffHeight()
    {
        return GetHeight(GetRightNode()) - GetHeight(GetLeftNode());
    }

    static int GetHeight(Node* node) { return node ? node->m_height : 0; }

private:
    int m_height = 1;
};

template<typename KeyType>
Node<KeyType>* Node<KeyType>::Insert(KeyType value)
{
    auto& ptr = value < GetValue() ?
                    GetLeftNode() :
                    GetRightNode();
    if (!ptr)
        ptr = new Node<KeyType>(std::move(value));
    else
        ptr = ptr->Insert(std::move(value));

    return BalanceIfNeeded();
}

template<typename KeyType>
void Node<KeyType>::UpdateHeight()
{
    m_height = std::max(GetHeight(GetLeftNode()), GetHeight(GetRightNode())) + 1;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::BalanceIfNeeded()
{
    UpdateHeight();
    const auto diff_heights = GetDiffHeight();
    if (abs(diff_heights) < 2)
        return this;

    if (diff_heights == 2) // right child height > left child
    {
        Node<KeyType>*& right_node = GetRightNode();
        if (right_node->GetDiffHeight() < 0)
            // his left is longer, then we need to do big left rotate (rotate right child  right and then left self)
            right_node = right_node->RotateRight();
        return RotateLeft();
    }
    Node<KeyType>*& left_node = GetLeftNode();
    if (left_node->GetDiffHeight() > 0)
        left_node = left_node->RotateLeft();
    return RotateRight();
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::RotateLeft()
{
    Node<KeyType>* right_child = GetRightNode();
    GetRightNode()             = right_child->GetLeftNode();
    right_child->GetLeftNode() = this;

    UpdateHeight();
    right_child->UpdateHeight();
    return right_child;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::RotateRight()
{
    Node<KeyType>* left_child  = GetLeftNode();
    GetLeftNode()              = left_child->GetRightNode();
    left_child->GetRightNode() = this;

    UpdateHeight();
    left_child->UpdateHeight();
    return left_child;
}
