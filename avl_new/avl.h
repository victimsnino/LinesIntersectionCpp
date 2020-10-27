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
    void Remove(const KeyType& value);

    const Node<KeyType>* FindNode(const KeyType& value) const;
private:
    Node<KeyType>* m_root = nullptr;
};

template<typename KeyType>
void AVLTree<KeyType>::Insert(KeyType value)
{
    m_root = Node<KeyType>::Insert(m_root, std::move(value));
}

template<typename KeyType>
void AVLTree<KeyType>::Remove(const KeyType& value)
{
    m_root = Node<KeyType>::Remove(m_root, value);
}

template<typename KeyType>
const Node<KeyType>* AVLTree<KeyType>::FindNode(const KeyType& value) const
{
    return Node<KeyType>::FindNode(m_root, value);
}
