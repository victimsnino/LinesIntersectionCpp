#pragma once

#include <memory>
#include "avl_node.h"

template<typename KeyType>
class AVLTree
{
public:
    void Insert(KeyType value);
    const BaseNode<KeyType>* FindNode(const KeyType& value) const;
private:
    std::unique_ptr<Node<KeyType>> m_root;
};

template<typename KeyType>
void AVLTree<KeyType>::Insert(KeyType value)
{
    if (m_root)
        m_root->Insert(std::move(value));
    else
        m_root = std::make_unique<Node<KeyType>>(std::move(value));
}

template<typename KeyType>
const BaseNode<KeyType>* AVLTree<KeyType>::FindNode(const KeyType& value) const
{
    const BaseNode<KeyType>* current = m_root.get();
    while(current)
    {
        const auto& cur_value = current->GetValue();
        if (cur_value == value)
            return current;

        current = value < cur_value ? current->GetLeftNode() : current->GetRightNode();
    }
    return nullptr;
}
