#pragma once

#include "avl_node.h"

template<typename KeyType>
class AVLTree
{
public:
    ~AVLTree()
    {
        delete m_root;
    }

    void Insert(KeyType value);
    const BaseNode<KeyType>* FindNode(const KeyType& value) const;
private:
    Node<KeyType>* m_root = nullptr;
};

template<typename KeyType>
void AVLTree<KeyType>::Insert(KeyType value)
{
    if (m_root)
        m_root = m_root->Insert(std::move(value));
    else
        m_root = new Node<KeyType>(std::move(value));
}

template<typename KeyType>
const BaseNode<KeyType>* AVLTree<KeyType>::FindNode(const KeyType& value) const
{
    const BaseNode<KeyType>* current = m_root;
    while(current)
    {
        const auto& cur_value = current->GetValue();
        if (cur_value == value)
            return current;

        current = value < cur_value ? current->GetLeftBaseNode() : current->GetRightBaseNode();
    }
    return nullptr;
}
