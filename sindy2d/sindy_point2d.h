#ifndef SINDY_POINT_H
#define SINDY_POINT_H

#include <math.h>

#define SINDY_DEFAULT_POINT_VAL 0.0
#define PRECISION 1e-8

namespace sindy
{
class Point2d
{
    double _x;
    double _y;

public:
    Point2d(double xx, double yy) : _x(xx), _y(yy) {}
    Point2d() : _x(SINDY_DEFAULT_POINT_VAL), _y(SINDY_DEFAULT_POINT_VAL) {}

    Point2d& operator=(const Point2d& other)
    {
        if (this == &other)
            return *this;
        _x = other._x;
        _y = other._y;
        return *this;
    }

    bool operator==(const Point2d& other) const
    {
        if (fabs(this->_x - other._x) <= PRECISION && fabs(this->_y - other._y) <= PRECISION)
            return true;
        return false;
    }

    inline double& x() { return _x; }
    inline double  x() const { return _x; }
    inline double& y() { return _y; }
    inline double  y() const { return _y; }

    inline double  operator*(const Point2d& pt) const { return _x * pt._x + _y * pt._y; }
    inline Point2d operator+(const Point2d& pt) const { return {_x + pt._x, _y + pt._y}; }
    inline Point2d operator-(const Point2d& pt) const { return {_x - pt._x, _y - pt._y}; }

    // 叉积
    inline double        cross(const Point2d& pt) const { return _x * pt._y - _y * pt._x; }
    inline static double cross(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d)
    {
        return Point2d(b - a).cross(Point2d(c - d));
    }
};

}  // namespace sindy

#endif  // !SINDY_POINT_H
