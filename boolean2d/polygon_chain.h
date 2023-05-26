#include <chrono>
#include <map>
#include <set>
#include <vector>

#include "../sindy2d/sindy_point2d.h"

using sindy::Point2d;

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

    // 获取单调链，vector<int>是单调链对应polygon每一个点的下标
    std::vector<std::vector<int>> getMonotoneChain(const std::vector<Point2d> &polygon);

    // 严格单调连+扫描线
    void SMC_SL(const std::vector<std::vector<int>> &chains, const std::vector<Point2d> &polygon, int pFlag);

    // 获取有序的扫描线,map:key为扫描线的x坐标，value为节点在该垂直扫描线上的严格单调链
    void PolygonChain::addSweepLine(const std::vector<Point2d> &polygon, const std::vector<int> &curChain, int pFlag);

    // 求相交的边
    std::vector<Point2d> getCrossPt(const std::vector<Point2d> &polygon1, const std::vector<Point2d> &polygon2);

    // 数学法求交点
    Point2d calcCrossPt(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4);

    // 包围盒碰撞检测
    bool collisionDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4);

    // 跨立检测
    bool crossDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4);
};