#include "sindy_box2d.h"

#include "float.h"

#define MY_EXTENTS_MAX -DBL_MAX
#define MY_EXTENTS_MIN DBL_MAX

bool compareDouble(double value1, double value2, double tol = SINDY_ZERO)
{
    double sub = value1 - value2;
    if (sub < 0)
        sub = -sub;

    if (sub <= tol)
        return true;
    return false;
}

namespace sindy
{
Box2d::Box2d() : m_min{MY_EXTENTS_MIN, MY_EXTENTS_MIN}, m_max{MY_EXTENTS_MAX, MY_EXTENTS_MAX}
{
}
Box2d::Box2d(const Point2d& pt) : m_min(pt), m_max(pt)
{
}
Box2d::Box2d(const std::initializer_list<Point2d>& list)
    : m_min{MY_EXTENTS_MIN, MY_EXTENTS_MIN}, m_max{MY_EXTENTS_MAX, MY_EXTENTS_MAX}
{
    for (const auto& point : list)
        add(point);
}

void Box2d::reset()
{
    m_min = {MY_EXTENTS_MIN, MY_EXTENTS_MIN};
    m_max = {MY_EXTENTS_MAX, MY_EXTENTS_MAX};
}
void Box2d::reset(const Point2d& pt1, const Point2d& pt2)
{
    m_min = pt1;
    m_max = pt1;
    add(pt2);
}
void Box2d::set(const Point2d& ptMin, const Point2d& ptMax)
{
    m_min = ptMin;
    m_max = ptMax;
}

// 建议使用前先判断有效性
bool Box2d::invalid() const
{
    if (compareDouble(m_min.x(), MY_EXTENTS_MIN) && compareDouble(m_min.y(), MY_EXTENTS_MIN) &&
        compareDouble(m_max.x(), MY_EXTENTS_MAX) && compareDouble(m_max.y(), MY_EXTENTS_MAX))
        return true;
    return false;
}
void Box2d::add(const Point2d& pt)
{
    if (pt.x() < m_min.x())
        m_min.x(pt.x());
    if (pt.x() > m_max.x())
        m_max.x(pt.x());

    if (pt.y() < m_min.y())
        m_min.y(pt.y());
    if (pt.y() > m_max.y())
        m_max.y(pt.y());
}
void Box2d::add(const Box2d& ext)
{
    add(ext.m_min);
    add(ext.m_max);
}
void Box2d::operator+=(const Box2d& ext)
{
    add(ext.m_min);
    add(ext.m_max);
}

bool Box2d::inBox(const Point2d& pt) const
{
    if (pt.x() < m_min.x() || pt.x() > m_max.x())
        return false;
    if (pt.y() < m_min.y() || pt.y() > m_max.y())
        return false;
    return true;
}
bool Box2d::inBox(const Point2d& pt, const double tol) const
{
    if (pt.x() < m_min.x() - tol || pt.x() > m_max.x() + tol)
        return false;
    if (pt.y() < m_min.y() - tol || pt.y() > m_max.y() + tol)
        return false;
    return true;
}
bool Box2d::outBox(const Point2d& pt) const
{
    if (pt.x() < m_min.x() || pt.x() > m_max.x())
        return true;
    if (pt.y() < m_min.y() || pt.y() > m_max.y())
        return true;
    return false;
}
bool Box2d::outBox(const Point2d& pt, const double tol) const
{
    if (pt.x() < m_min.x() - tol || pt.x() > m_max.x() + tol)
        return true;
    if (pt.y() < m_min.y() - tol || pt.y() > m_max.y() + tol)
        return true;
    return false;
}
bool Box2d::outBox(const Box2d& ext) const
{
    if (ext.m_max.x() < m_min.x() || ext.m_min.x() > m_max.x())
        return true;
    if (ext.m_max.y() < m_min.y() || ext.m_min.y() > m_max.y())
        return true;
    return false;
}
bool Box2d::outBox(const Box2d& ext, const double tol) const
{
    if (ext.m_max.x() < m_min.x() - tol || ext.m_min.x() > m_max.x() + tol)
        return true;
    if (ext.m_max.y() < m_min.y() - tol || ext.m_min.y() > m_max.y() + tol)
        return true;
    return false;
}

void Box2d::expand(double value)
{
    m_min -= value;
    m_max += value;
}

void Box2d::moveTo(const Point2d& ptNewCenter)
{
    Point2d ptCurCenter{(m_max.x() * 0.5 + m_min.x() * 0.5), (m_max.y() * 0.5 + m_min.y() * 0.5)};
    Point2d offset(ptNewCenter.x() - ptCurCenter.x(), ptNewCenter.y() - ptCurCenter.y());

    m_min += offset;
    m_max += offset;
}

Point2d Box2d::centerPt() const
{
    return {(m_max.x() * 0.5 + m_min.x() * 0.5), (m_max.y() * 0.5 + m_min.y() * 0.5)};
}

} // namespace sindy
