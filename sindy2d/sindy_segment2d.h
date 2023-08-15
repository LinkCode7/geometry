#ifndef SINDY_SEGMENT2D_H
#define SINDY_SEGMENT2D_H

#include "sindy_geometry.h"
#include "sindy_point2d.h"

namespace sindy
{
class Arc2d;

class Segment2d : public Geometry
{
    Point2d _begin;
    Point2d _end;

public:
    Segment2d() {}
    Segment2d(Point2d const& begin, Point2d const& end) : _begin(begin), _end(end) {}
    Segment2d(Segment2d&& other) : _begin(std::move(other._begin)), _end(std::move(other._end)) {}

    Segment2d(Segment2d const&) = delete;
    Segment2d& operator=(Segment2d const&) = delete;

public:
    Point2d begin() const override { return _begin; }
    void    begin(Point2d const& value) { _begin = value; }

    Point2d end() const { return _end; }
    void    end(Point2d const& value) { _end = value; }

    double length() const override { return (_begin - _end).length(); }

public:
    int intersection(Segment2d const& seg, std::vector<Point2d>& result) const;

    int intersection(Arc2d const& arc, std::vector<Point2d>& result) const;
};
} // namespace sindy

#endif // !SINDY_SEGMENT2D_H
