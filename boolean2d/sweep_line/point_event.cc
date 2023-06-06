#include "point_event.h"

bool PointEvent::operator<(const PointEvent& other) const
{
    if (bg::get<0>(this->m_point2d) != bg::get<0>(other.m_point2d))
        return bg::get<0>(this->m_point2d) < bg::get<0>(other.m_point2d);
    else if (bg::get<1>(this->m_point2d) != bg::get<1>(other.m_point2d))
        return bg::get<1>(this->m_point2d) < bg::get<1>(other.m_point2d);
    else
        return this->m_eventType < other.m_eventType;
}

bool PointEvent::operator>(const PointEvent& other) const
{
    if (bg::get<0>(this->m_point2d) != bg::get<0>(other.m_point2d))
        return bg::get<0>(this->m_point2d) > bg::get<0>(other.m_point2d);
    else if (bg::get<1>(this->m_point2d) != bg::get<1>(other.m_point2d))
        return bg::get<1>(this->m_point2d) > bg::get<1>(other.m_point2d);
    else
        return this->m_eventType > other.m_eventType;
}
