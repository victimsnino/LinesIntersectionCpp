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
        return GetHeight(BaseNode<KeyType>::GetRightNode()) - GetHeight(BaseNode<KeyType>::GetLeftNode());
    }

    static int GetHeight(Node* node) { return node ? node->m_height : 0; }

private:
    int m_height = 1;
};

template<typename KeyType>
Node<KeyType>* Node<KeyType>::Insert(KeyType value)
{
    auto& ptr = value < BaseNode<KeyType>::GetValue() ?
                    BaseNode<KeyType>::GetLeftNode() :
                    BaseNode<KeyType>::GetRightNode();
    if (!ptr)
        ptr = new Node<KeyType>(std::move(value));
    else
        ptr = ptr->Insert(std::move(value));

    return BalanceIfNeeded();
}

template<typename KeyType>
void Node<KeyType>::UpdateHeight()
{
    m_height = std::max(GetHeight(BaseNode<KeyType>::GetLeftNode()), GetHeight(BaseNode<KeyType>::GetRightNode())) + 1;
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
        Node<KeyType>*& right_node = BaseNode<KeyType>::GetRightNode();
        if (right_node->GetDiffHeight() < 0)
            // his left is longer, then we need to do big left rotate (rotate right child  right and then left self)
            right_node = right_node->RotateRight();
        return RotateLeft();
    }
    Node<KeyType>*& left_node = BaseNode<KeyType>::GetLeftNode();
    if (left_node->GetDiffHeight() > 0)
        left_node = left_node->RotateLeft();
    return RotateRight();
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::RotateLeft()
{
    Node<KeyType>* right_child                    = BaseNode<KeyType>::GetRightNode();
    BaseNode<KeyType>::GetRightNode()             = right_child->BaseNode<KeyType>::GetLeftNode();
    right_child->BaseNode<KeyType>::GetLeftNode() = this;

    UpdateHeight();
    right_child->UpdateHeight();
    return right_child;
}

template<typename KeyType>
Node<KeyType>* Node<KeyType>::RotateRight()
{
    Node<KeyType>* left_child                     = BaseNode<KeyType>::GetLeftNode();
    BaseNode<KeyType>::GetLeftNode()              = left_child->BaseNode<KeyType>::GetRightNode();
    left_child->BaseNode<KeyType>::GetRightNode() = this;

    UpdateHeight();
    left_child->UpdateHeight();
    return left_child;
}
