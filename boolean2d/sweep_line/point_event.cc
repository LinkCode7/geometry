#include "point_event.h"

bool PointEvent::operator==(const PointEvent& other) const
{
    if (!(*this < other) && !(*this > other))
        return true;
    else
        return false;
}

bool PointEvent::operator<(const PointEvent& other) const
{
    if (IS_FLOAT_EQUAL(bg::get<0>(this->m_point2d), bg::get<0>(other.m_point2d)))
    {
        if (IS_FLOAT_EQUAL(bg::get<1>(this->m_point2d), bg::get<1>(other.m_point2d)))
            return this->m_eventType < other.m_eventType;
        else
            return bg::get<1>(this->m_point2d) < bg::get<1>(other.m_point2d);
    }
    else
        return bg::get<0>(this->m_point2d) < bg::get<0>(other.m_point2d);
}

bool PointEvent::operator>(const PointEvent& other) const
{
    if (IS_FLOAT_EQUAL(bg::get<0>(this->m_point2d), bg::get<0>(other.m_point2d)))
    {
        if (IS_FLOAT_EQUAL(bg::get<1>(this->m_point2d), bg::get<1>(other.m_point2d)))
            return this->m_eventType > other.m_eventType;
        else
            return bg::get<1>(this->m_point2d) > bg::get<1>(other.m_point2d);
    }
    else
        return bg::get<0>(this->m_point2d) > bg::get<0>(other.m_point2d);
}
