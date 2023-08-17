#ifndef SINDY_MATH_H
#define SINDY_MATH_H
#include <vector>

#include "sindy_arc2d.h"
#include "sindy_point2d.h"
#include "sindy_segment2d.h"

using FloatType = double;

static const FloatType Epsilon_Medium = 1.0E-10;
static const FloatType Epsilon_Low    = 1.0E-07;
static const FloatType Epsilon        = Epsilon_Medium;

namespace sindy
{
// 判断点c是否在线段ab上
bool isPtInLine(Point2d const& a, Point2d const& b, Point2d const& c);
// 判断两条线段是否相交
bool isIntersect(Point2d const& a, Point2d const& b, Point2d const& c, Point2d const& d);
// 求两条线段的交点，可能有0,1,2个交点
int intersection(Point2d const& a, Point2d const& b, Point2d const& c, Point2d const& d, std::vector<Point2d>& result);

inline bool isEqual(double val1, double val2, double epsilon)
{
    double diff = val1 - val2;

#ifdef _DEBUG
    assert(((-epsilon <= diff) && (diff <= epsilon)) == (abs(diff) <= epsilon));
#endif

    return ((-epsilon <= diff) && (diff <= epsilon));
}

inline bool lessThanOrEqual(double val1, double val2, double epsilon = Epsilon)
{
    return (val1 < val2) || isEqual(val1, val2, epsilon);
}

inline double getAbs(double dValue)
{
    if (dValue > 0)
        return dValue;
    else
        return -dValue;
}

// 比较两个浮点数：0表示相同 1表示前面大 -1表示后面大
inline int compare(double src1, double src2, double tol = SINDY_ZERO)
{
    double dblSub = src1 - src2;
    if (getAbs(dblSub) <= tol)
        return 0; // 相同
    else if (dblSub > tol)
        return 1;
    else
        return -1;
}

// true:圆弧从起点到终点是顺时针方向
bool isArcClockwise(Point2d const& begin, Point2d const& end, Point2d const& center);

} // namespace sindy

#endif // !SINDY_MATH_H
