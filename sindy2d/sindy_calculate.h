#ifndef SINDY_CALCULATE_H
#define SINDY_CALCULATE_H
#include <vector>

#include "../common.h"
#include "../sindy2d/sindy_point2d.h"
#ifdef _DEBUG
    #include <cassert>
#endif

using Float = double;

static const Float Epsilon_Medium = 1.0E-10;
static const Float Epsilon_Low    = 1.0E-07;
static const Float Epsilon        = Epsilon_Medium;

namespace sindy
{
// 判断点c是否在线段ab上
bool isPtInLine(const Point2d& a, const Point2d& b, const Point2d& c);
// 判断两条线段是否相交
bool isIntersect(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d);
// 求两条线段的交点，可能有0,1,2,3,4个交点
int intersectionPoint(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d, std::vector<Point2d>& result);

inline bool isEqual(double val1, double val2, double epsilon)
{
    double diff = val1 - val2;
    assert(((-epsilon <= diff) && (diff <= epsilon)) == (abs(diff) <= epsilon));
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
        return 0;  // 相同
    else if (dblSub > tol)
        return 1;
    else
        return -1;
}

}  // namespace sindy

#endif  // !SINDY_CALCULATE_H
