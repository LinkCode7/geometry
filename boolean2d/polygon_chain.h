#ifndef POLYGON_CHAIN_H
#define POLYGON_CHAIN_H

#include <chrono>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

#include "../sindy2d/sindy_point2d.h"

using sindy::Point2d;

// 多边形链求交算法
class PolygonChain
{
    std::map<double, std::set<std::pair<std::vector<int>, int>>> sweepLine;

public:
    PolygonChain(){};
    std::vector<Point2d> doItersect(const std::vector<Point2d> &polygon1, const std::vector<Point2d> &polygon2);

private:
    // TODO : 获取所有凸凹链、获取最优扫描线方向、旋转多边形
    void   getConvexChain(const std::vector<Point2d> &polygon);
    double getSweepDirection();
    void   rotatePolygon();

    // 获取单调链
    std::vector<std::vector<int>> getMonotoneChain(const std::vector<Point2d> &polygon);

    // 获取严格单调链，扫描线
    void SMC_SL(const std::vector<std::vector<int>> &chains, const std::vector<Point2d> &polygon, int pFlag);

    // 获取有序的扫描线
    void PolygonChain::addSweepLine(const std::vector<Point2d> &polygon, const std::vector<int> &curChain, int pFlag);

    // 求相交的边
    std::vector<Point2d> getCrossPt(const std::vector<Point2d> &polygon1, const std::vector<Point2d> &polygon2);

    // 数学法求交点
    Point2d calcCrossPt(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4);

    // 包围盒碰撞检测
    bool collisionDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4);

    // 跨立检测
    bool crossDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4);

    // 检测点是否在线段
    bool onLineDect(const Point2d &p, const Point2d &p1, const Point2d &p2);

    // 距离公式
    inline double distance(const Point2d &p1, const Point2d &p2) { return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2)); };
};
#endif  // !POLYGON_CHAIN_H