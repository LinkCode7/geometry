#include "priority_queue.h"

// TODO: push 后要调整堆
template <typename T>
void PriorityQueue<T>::push(const T& t)
{
    m_vector.push_back(t);
}

template <typename T>
T PriorityQueue<T>::front()
{
    return m_vector[0];
}

template <typename T>
T PriorityQueue<T>::back()
{
    return m_vector[m_vector.size() - 1];
}

template <typename T>
void PriorityQueue<T>::pop_front()
{
    m_vector.erase(m_vector.begin());
}

template <typename T>
void PriorityQueue<T>::pop_back()
{
    m_vector.erase(--m_vector.end());
}
