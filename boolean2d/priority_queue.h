#pragma once

#include <vector>

template <typename T>
class PriorityQueue
{
public:
    PriorityQueue() {}

    void push(const T& t);
    T    front();
    T    back();
    void pop_front();
    void pop_back();

    // TODO: 改成 private 和指针
public:
    // TODO: 用树还是 vector
    std::vector<T> m_vector;
};
