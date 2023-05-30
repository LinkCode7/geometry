#ifndef POLYGON_CHAIN_H
#define POLYGON_CHAIN_H

#include <chrono>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

#include "../sindy2d/sindy_point2d.h"

#define PRECISION 1e-8

using sindy::Point2d;

// 多边形链求交算法
/*
    1.确定多边形中的所有左右极值点
    2.根据所有的左右极值点，获得所有的单调链
    3.将单调链细分为严格单调链（包括严格单调增链和严格单调减链）
    4.在细分严格单调增链过程中，同时获取并按照x坐标排序扫描线
    5.遍历扫描线，加入以该扫描线交点为左极值点的严格单调链，删除该交点为右极值点的严格单调链
    6.对严格单调链进行两两求交
    7.具体严格单调链两两之间的求交过程：
        7.1 计算两严格单调链的包围盒，如果无碰撞，则说明无交点
        7.2 如果有碰撞，再次对两严格单调链上的边进行一一进行碰撞检测和跨立检测

    尚未实现的优化：获取所有凸凹链、获取最优扫描线方向、旋转多边形

    参考文献：《Polygonal Chain Intersection》，《多边形链求交的改进算法》
*/

class PolygonChain
{
    std::map<double, std::set<std::pair<std::vector<int>, int>>> m_sweepLines;

public:
    PolygonChain(){};
    std::vector<Point2d> doItersect(const std::vector<Point2d> &polygon1, const std::vector<Point2d> &polygon2);

private:
    // TODO : 获取所有凸凹链、获取最优扫描线方向、旋转多边形
    void   getConvexChain(const std::vector<Point2d> &polygon);
    double getSweepDirection();
    void   rotatePolygon();

    // 获取单调链（单调链：沿扫描线方向（默认为x轴方向），点x坐标依次递增的链称为单调链）
    std::vector<std::vector<int>> getMonotoneChain(const std::vector<Point2d> &polygon) const;

    // 获取严格单调链，扫描线
    void getSMChainSweepLine(const std::vector<std::vector<int>> &chains, const std::vector<Point2d> &polygon, int pFlag);

    // 获取有序的扫描线（扫描线：过严格单调链起点或终点，且垂直于扫描线方向(默认为x轴)的线）
    void PolygonChain::addSweepLine(const std::vector<Point2d> &polygon, const std::vector<int> &curChain, int pFlag);

    // 求相交的边
    std::vector<Point2d> getCrossPt(const std::vector<Point2d> &polygon1, const std::vector<Point2d> &polygon2) const;

    // 数学公式法求交点
    Point2d calcCrossPt(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4) const;

    // 线段求交（包围盒检测）
    bool collisionDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4) const;

    // 线段求交（跨立检测）
    bool crossDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4) const;

    // 检测点是否在线段
    bool onLineDect(const Point2d &p, const Point2d &p1, const Point2d &p2) const;

    // 两点间距离公式
    inline double distance(const Point2d &p1, const Point2d &p2) const { return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2)); };
};
#endif  // !POLYGON_CHAIN_H