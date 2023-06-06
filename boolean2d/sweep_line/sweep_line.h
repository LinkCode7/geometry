#pragma once

#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

#include "../boolean_geometry_pch.h"
#include "point_event.h"
#include "segment.h"

// TODO: 抽象
struct Segment2dCompare
{
    bool operator()(const Segment2d& firstSegment2d, const Segment2d& secondSegment2d) const  // 最后的const不能少
    {
        if (bg::get<0>(firstSegment2d.GetSweepLineCrossPoint()) != bg::get<0>(secondSegment2d.GetSweepLineCrossPoint()))
            return bg::get<0>(firstSegment2d.GetSweepLineCrossPoint()) < bg::get<0>(secondSegment2d.GetSweepLineCrossPoint());
        else
            return bg::get<1>(firstSegment2d.GetSweepLineCrossPoint()) < bg::get<1>(secondSegment2d.GetSweepLineCrossPoint());
    }
};

struct Point2dHash
{
    size_t operator()(const point_2d point2d) const  // size_t
    {
        // return size_t(l.k ^ l.b);//自定义哈希
        return std::hash<double>()(bg::get<0>(point2d)) ^ std::hash<double>()(bg::get<1>(point2d));
    }
};

struct Point2dIsEqual
{
    bool operator()(const point_2d firstPoint2d, const point_2d secondPoint2d) const  // 最后的const不能少
    {
        return bg::get<0>(firstPoint2d) == bg::get<0>(secondPoint2d) && bg::get<1>(firstPoint2d) == bg::get<1>(secondPoint2d);
    }
};

typedef std::unordered_set<point_2d, Point2dHash, Point2dIsEqual> point2d_unordered_set;

class SweepLine
{
public:
    // SweepLine() {}
    SweepLine(std::vector<segment_2d>& segmentVec);
    SweepLine(std::vector<Segment2d>& segmentVec);
    ~SweepLine() {}

    inline point2d_unordered_set GetAllCrossPoints() { return m_allCrossPoints; }

    void PrintPointQueue();
    void PrintSegmentTree();

    // 预处理函数
    void ResetSegmentsPoints(std::vector<segment_2d>& segments);

    void UpdateSegmentTree(double sweepLineXPos, double sweepLineYPos);
    void EmplaceCrossPoint(int& a, int& b);
    void Scan();

private:
    std::priority_queue<PointEvent, std::vector<PointEvent>, std::greater<PointEvent>> m_pointQueue;
    point2d_unordered_set  m_allCrossPoints;  // TODO: 不知道交点查找起来有什么规律，暂时用 hash 存
    std::vector<Segment2d> m_segmentTree;     // TODO: 用树得自定义数据结构，只能先用 vector 了
    double                 m_sweepLineXPos;   // 扫描线位置
};