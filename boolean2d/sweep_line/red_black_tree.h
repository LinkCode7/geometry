# #pragma once

enum class RBTColor
{
    Red,
    Black,
};

template <class T>
class RBTNode
{
public:
    RBTNode() : m_key(0), m_color(RBTColor::Black), m_leftNode(nullptr), m_rightNode(nullptr), m_parentNode(nullptr) {}
    RBTNode(T const& key, RBTColor color) : m_key(key), m_color(color), m_leftNode(nullptr), m_rightNode(nullptr), m_parentNode(nullptr) {}
    RBTNode(T key, RBTColor color, RBTNode leftNode, RBTNode rightNode, RBTNode parentNode)
        : m_key(key), m_color(color), m_leftNode(leftNode), m_rightNode(rightNode), m_parentNode(parentNode)
    {
    }
    ~RBTNode()
    {
        delete m_leftNode;
        delete m_rightNode;
        delete m_parentNode;
    }

private:
    T        m_key;
    RBTColor m_color;
    RBTNode* m_leftNode;
    RBTNode* m_rightNode;
    RBTNode* m_parentNode;
};

template <class T>
class RBTree
{
public:
private:
    RBTNode<T>* m_root;
};