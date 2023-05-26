#include "sindy_calculate.h"

#include "sindy_extents2d.h"

bool sindy::isPtInLine(const Point2d& a, const Point2d& b, const Point2d& c)
{
    Point2d pt1(c - a);
    Point2d pt2(c - b);
    auto    cross = pt1.x() * pt2.y() - pt1.y() * pt2.x();  // 叉积
    // 点c在ab的直线上
    if (compare(cross, 0.0) != 0)
        return false;

    // 点c不在直线ab的延长线上
    Extents2d ext({a, b});
    if (ext.outExtents(c))
        return false;
    return true;
}

bool sindy::isIntersect(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d)
{
    // 1. 碰撞检测
    if (Extents2d{a, b}.outExtents(Extents2d{c, d}))
        return false;

    // 2. 跨立检测
    // 点a、b在线段cd的两侧，则有：
    auto dc = c - d;
    if ((a - d).cross(dc) * (b - d).cross(dc) <= 0.0)  // ad、bd位于cd两侧
    {
        // 点c、d在线段ab的两侧，则有：
        auto ba = a - b;
        if ((c - b).cross(ba) * (d - b).cross(ba) <= 0.0)  // cb、db位于ab两侧
            return true;
    }

    return false;
}

// 判断两条线段是否相交
// 如果两线段相交，则两线段必然相互跨立对方,通过叉积来做判断即可。但需要先使用快速排斥试验处理可能的共线等问题。
// x1,y1,x2,y2为第一个线段的两个点；x3,y3,x4,y4为第二个线段的两个点。
bool is_segment_cross(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    // 先使用快速排斥试验进行判断，同时排除两条线段共线的情况
    if (std::max(x1, x2) < std::min(x3, x4) || std::max(y1, y2) < std::min(y3, y4) || std::min(x1, x2) > std::max(x3, x4) ||
        std::min(y1, y2) > std::max(y3, y4))
        return false;

    // 使用跨立试验进行相交判断
    if (((x3 - x1) * (y3 - y4) - (y3 - y1) * (x3 - x4)) * ((x3 - x2) * (y3 - y4) - (y3 - y2) * (x3 - x4)) <= 0 &&
        ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) * ((x1 - x4) * (y1 - y2) - (y1 - y4) * (x1 - x2)) <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int sindy::intersectionPoint(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d, std::vector<Point2d>& result)
{
    return 0;
}
