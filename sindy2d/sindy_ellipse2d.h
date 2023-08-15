#ifndef SINDY_ELLIPSE_H
#define SINDY_ELLIPSE_H

#include "sindy_geometry.h"
#include "sindy_point2d.h"

namespace sindy
{
/*
 * @brief 椭圆弧
 * @detail 所有涉及角度的值均采用弧度制
 */
class Ellipse2d : public Geometry
{
    Point2d _begin;            // 起点
    Point2d _end;              // 终点
    Point2d _center;           // 圆心
    double  _radiusX    = 0.0; // X轴半径
    double  _radiusY    = 0.0; // Y轴半径
    double  _beginAngle = 0.0; // 起点角度
    double  _sweepAngle = 0.0; // 扫掠角度

public:
    Ellipse2d(Ellipse2d const&) = delete;
    Ellipse2d& operator=(Ellipse2d const&) = delete;

public:
    Point2d begin() const override { return _begin; }
    void    begin(Point2d const& value) { _begin = value; }

    Point2d end() const { return _end; }
    void    end(Point2d const& value) { _end = value; }

    Point2d center() const { return _center; }
    void    center(Point2d const& value) { _center = value; }

    double radiusX() const { return _radiusX; }
    void   radiusX(double value) { _radiusX = value; }
    double radiusY() const { return _radiusY; }
    void   radiusY(double value) { _radiusY = value; }

    double beginAngle() const { return _beginAngle; }
    void   beginAngle(double value) { _beginAngle = value; }

    double endAngle() const { return _beginAngle + _sweepAngle; }

    double sweepAngle() const { return _sweepAngle; }
    void   sweepAngle(double value) { _sweepAngle = value; }

    ClockDirection direction() const
    {
        return _sweepAngle >= 0.0 ? ClockDirection::eCounterClockwise : ClockDirection::eClockwise;
    }
    bool isCCW() const { return _sweepAngle >= 0.0; }

public:
    double length() const override { return (_begin - _end).length(); }

    Point2d getPoint(double radian) const;
};
} // namespace sindy

#endif // !SINDY_ELLIPSE_H