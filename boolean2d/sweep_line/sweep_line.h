#pragma once

#include <iterator>
#include <map>
#include <queue>
#include <set>

#include "../boolean_pch.h"
#include "point_event.h"
#include "segment.h"

class SweepLine
{
public:
    // SweepLine() {}
    SweepLine(std::vector<segment_2d>& segmentVec);
    SweepLine(std::vector<polygon_2d> const& polygonVec);
    ~SweepLine() {}

    inline point2d_unordered_set GetAllCrossPoints() const { return m_allCrossPoints; }

private:
    // 预处理函数
    void                    resetSegmentsPoints(std::vector<segment_2d>& segments);
    std::vector<segment_2d> disjointPolygons(std::vector<polygon_2d> const& polygonVec);

    void updateSegmentTree(double sweepLineXPos, double sweepLineYPos);
    void emplaceCrossPoint(int& a, int& b); // 用引用是为了改成红黑树的时候方便

public:
    void scan();

private:
    std::priority_queue<PointEvent, std::vector<PointEvent>, std::greater<PointEvent>>
                           m_pointQueue;     // 存储点事件的优先队列 ，排序规则在 point_event 里
    point2d_unordered_set  m_allCrossPoints; // TODO: 不知道交点查找起来有什么规律，暂时用 hash 存
    std::vector<Segment2d> m_segmentTree;    // TODO: 用 mutil_set 试试
};