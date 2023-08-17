#include "segment.h"

Segment2d::Segment2d(PointEvent const& pointEvent, PointEvent const& anotherPointEvent)
{
    if (pointEvent.getEventType() == EventType::StartPoint)
    {
        m_segment2d.first  = pointEvent.getPoint();
        m_segment2d.second = anotherPointEvent.getPoint();
        m_startPointEvent  = pointEvent;
    }
    else
    {
        m_segment2d.first  = anotherPointEvent.getPoint();
        m_segment2d.second = pointEvent.getPoint();
        m_startPointEvent  = anotherPointEvent;
    }

    m_sweepLineCrossPoint = m_segment2d.first;

    if (bg::get<0>(m_segment2d.first) == bg::get<0>(m_segment2d.second))
    {
        m_isNoK = true;
        m_k     = 0;
    }
    else
    {
        m_isNoK = false;
        m_k     = (bg::get<1>(m_segment2d.second) - bg::get<1>(m_segment2d.first)) /
              (bg::get<0>(m_segment2d.second) - bg::get<0>(m_segment2d.first));
    }
}

Segment2d Segment2d::operator=(Segment2d const& other)
{
    this->m_segment2d           = other.m_segment2d;
    this->m_startPointEvent     = other.m_startPointEvent;
    this->m_sweepLineCrossPoint = other.m_sweepLineCrossPoint;
    this->m_k                   = other.m_k;
    this->m_isNoK               = other.m_isNoK;
    return *this;
}

bool Segment2d::operator==(Segment2d const& other) const
{
    if (!(*this < other) && !(*this > other))
        return true;
    else
        return false;
}

// 默认从左下到右上
bool Segment2d::operator<(Segment2d const& other) const
{
    if (!IS_FLOAT_EQUAL(bg::get<0>(this->m_segment2d.first), bg::get<0>(other.m_segment2d.first)))
        return bg::get<0>(this->m_segment2d.first) < bg::get<0>(other.m_segment2d.first);
    else if (!IS_FLOAT_EQUAL(bg::get<1>(this->m_segment2d.first), bg::get<1>(other.m_segment2d.first)))
        return bg::get<1>(this->m_segment2d.first) < bg::get<1>(other.m_segment2d.first);
    else if (!IS_FLOAT_EQUAL(bg::get<0>(this->m_segment2d.second), bg::get<0>(other.m_segment2d.second)))
        return bg::get<0>(this->m_segment2d.second) < bg::get<0>(other.m_segment2d.second);
    else
        return bg::get<1>(this->m_segment2d.second) < bg::get<1>(other.m_segment2d.second);
}

// 默认从左下到右上
bool Segment2d::operator>(Segment2d const& other) const
{
    if (!IS_FLOAT_EQUAL(bg::get<0>(this->m_segment2d.first), bg::get<0>(other.m_segment2d.first)))
        return bg::get<0>(this->m_segment2d.first) > bg::get<0>(other.m_segment2d.first);
    else if (!IS_FLOAT_EQUAL(bg::get<1>(this->m_segment2d.first), bg::get<1>(other.m_segment2d.first)))
        return bg::get<1>(this->m_segment2d.first) > bg::get<1>(other.m_segment2d.first);
    else if (!IS_FLOAT_EQUAL(bg::get<0>(this->m_segment2d.second), bg::get<0>(other.m_segment2d.second)))
        return bg::get<0>(this->m_segment2d.second) > bg::get<0>(other.m_segment2d.second);
    else
        return bg::get<1>(this->m_segment2d.second) > bg::get<1>(other.m_segment2d.second);
}

std::ostream& operator<<(std::ostream& out, Segment2d const& other)
{
    // double x0 = bg::get<0, 0>(segment);
    // double y0 = bg::get<0, 1>(segment);
    // double x1 = bg::get<1, 0>(segment);
    // double y1 = bg::get<1, 1>(segment);
    out << "x1: " << bg::get<0, 0>(other.m_segment2d) << ", y1: " << bg::get<0, 1>(other.m_segment2d)
        << ", x2: " << bg::get<1, 0>(other.m_segment2d) << ", y2: " << bg::get<1, 1>(other.m_segment2d);
    return out;
}

// 默认扫描线垂直 x 轴，从左到右，不好改扫描线方向，改的话比较函数也要一起改
void Segment2d::updateSweepLineCrossPoint(double x, double y)
{
    if (m_isNoK)
    {
        bg::set<1>(m_sweepLineCrossPoint, y);
    }
    else
    {
        bg::set<0>(m_sweepLineCrossPoint, x);
        bg::set<1>(m_sweepLineCrossPoint, m_k * (x - bg::get<0>(m_segment2d.first)) + bg::get<1>(m_segment2d.first));
    }
}
