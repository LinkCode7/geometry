#include "point_event.h"

bool PointEvent::operator==(PointEvent const& other) const
{
    if (!(*this < other) && !(*this > other))
        return true;
    else
        return false;
}

// 坐标值相同的节点事件在排序时
// 1. 首先应该把终点放在起点前面
// 2. 其次如果都是起点再继续比较另一个端点（终点）的纵坐标（优先）和横坐标。
bool PointEvent::operator<(PointEvent const& other) const
{
    if (!IS_FLOAT_EQUAL(bg::get<0>(this->m_point2d), bg::get<0>(other.m_point2d)))
        return bg::get<0>(this->m_point2d) < bg::get<0>(other.m_point2d);
    else if (!IS_FLOAT_EQUAL(bg::get<1>(this->m_point2d), bg::get<1>(other.m_point2d)))
        return bg::get<1>(this->m_point2d) < bg::get<1>(other.m_point2d);
    else if (this->m_eventType != other.m_eventType)
        return this->m_eventType < other.m_eventType;
    else if (!IS_FLOAT_EQUAL(bg::get<1>(this->m_otherEventSP->m_point2d), bg::get<1>(other.m_otherEventSP->m_point2d)))
        return bg::get<1>(this->m_otherEventSP->m_point2d) < bg::get<1>(other.m_otherEventSP->m_point2d);
    else
        return bg::get<0>(this->m_otherEventSP->m_point2d) < bg::get<0>(other.m_otherEventSP->m_point2d);
}

// 坐标值相同的节点事件在排序时
// 1. 首先应该把终点放在起点前面
// 2. 其次如果都是起点再继续比较另一个端点（终点）的纵坐标（优先）和横坐标。
bool PointEvent::operator>(PointEvent const& other) const
{
    if (!IS_FLOAT_EQUAL(bg::get<0>(this->m_point2d), bg::get<0>(other.m_point2d)))
        return bg::get<0>(this->m_point2d) > bg::get<0>(other.m_point2d);
    else if (!IS_FLOAT_EQUAL(bg::get<1>(this->m_point2d), bg::get<1>(other.m_point2d)))
        return bg::get<1>(this->m_point2d) > bg::get<1>(other.m_point2d);
    else if (this->m_eventType != other.m_eventType)
        return this->m_eventType > other.m_eventType;
    else if (!IS_FLOAT_EQUAL(bg::get<1>(this->m_otherEventSP->m_point2d), bg::get<1>(other.m_otherEventSP->m_point2d)))
        return bg::get<1>(this->m_otherEventSP->m_point2d) > bg::get<1>(other.m_otherEventSP->m_point2d);
    else
        return bg::get<0>(this->m_otherEventSP->m_point2d) > bg::get<0>(other.m_otherEventSP->m_point2d);
}
