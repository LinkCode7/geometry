#ifndef SINDY_EXTENTS2D_H
#define SINDY_EXTENTS2D_H
#include <initializer_list>

#include "../common.h"
#include "../sindy2d/SindyPoint2d.h"

namespace sindy
{
// 用一个最小的平行于坐标轴的矩形来框住几何体：Minimum Bounding Box
class Extents2d
{
    Point2d m_min;
    Point2d m_max;

public:
    Extents2d();
    Extents2d(const Point2d& pt);
    explicit Extents2d(const std::initializer_list<Point2d>& list);
    void           set(const Point2d& ptMin, const Point2d& ptMax);
    inline Point2d min() const { return m_min; }
    inline Point2d max() const { return m_max; }

    void    reset();
    void    reset(const Point2d& pt1, const Point2d& pt2);
    bool    invalid() const;
    Point2d centerPt() const;
    void    expand(double value);  // 扩大或缩小(负数)包络
    void    moveTo(const Point2d& ptNewCenter);

    void addPoint(const Point2d& pt);
    void addExtents(const Extents2d& ext);
    void operator+=(const Extents2d& ext);
    bool inExtents(const Point2d& pt) const;
    bool inExtents(const Point2d& pt, double tol) const;
    bool outExtents(const Point2d& pt) const;
    bool outExtents(const Point2d& pt, double tol) const;
    bool outExtents(const Extents2d& ext) const;
    bool outExtents(const Extents2d& ext, double tol) const;
};

}  // namespace sindy

#endif  // !SINDY_EXTENTS2D_H