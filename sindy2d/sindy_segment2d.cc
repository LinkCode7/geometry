#include "sindy_segment2d.h"

#include "sindy_arc2d.h"

namespace sindy
{
int Segment2d::intersection(Segment2d const& seg, std::vector<Point2d>& result) const
{
    return 0;
}

int Segment2d::intersection(Arc2d const& arc, std::vector<Point2d>& result) const
{
    return 0;
}

std::vector<Point2d> Segment2d::segment(double unitLength) const
{
    std::vector<Point2d> result;
    return result;
}

} // namespace sindy
